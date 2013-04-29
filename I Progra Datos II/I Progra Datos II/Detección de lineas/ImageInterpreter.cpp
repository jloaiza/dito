
#include "ImageInterpreter.h"

#include <iostream>
#include <opencv2/highgui/highgui_c.h>
using namespace std;

#define RANGE 50
#define TEMP_SLOPE1 5
#define TEMP_SLOPE2 15

ImageInterpreter::ImageInterpreter(){
    _lines = new DoubleLinkedList<line>();
}

void ImageInterpreter::analize(char* pPath, CvPoint pAreaS, CvPoint pAreaF){
    
    IplImage* image = cvLoadImage(pPath); //Se carga la imágen
    
    //Se obtiene imagen binaria de un solo canal
    IplImage* bn = cvCreateImage(cvGetSize(image), image->depth, 1);
    cvCvtColor(image, bn, CV_RGB2GRAY);
    cvThreshold(bn, bn ,1, 255, CV_THRESH_BINARY);
        
    //Analisis superior del área de restauración
    topAnalizeAux(bn, pAreaS, pAreaF);
    
    //Análisis del lado izquierdo del AR
    leftAnalizeAux(bn, pAreaS, pAreaF);
    
    //Análisis lado derecho del AR
    rightAnalizeAux(bn, pAreaS, pAreaF);
    
    //Análisis lado inferior del AR
    bottomAnalizeAux(bn, pAreaS, pAreaF);
    
    //------------miscellaneous----------------PINTAR LAS LINEAS - NO ES NECESARIO------------------------
    cout<<"miscellaneous"<<endl;
    cvRectangle(image, pAreaS, pAreaF, cvScalar(255, 0, 0), 2);
    cvNamedWindow("img");
    ListNode<line>* iNode = _lines->getHead();
    cvShowImage("img", bn);
    cvWaitKey();
    while (iNode != 0){
        cout<<"n"<<endl;
        CvPoint p1 = cvPoint(iNode->getData()->sx, iNode->getData()->sy);
        CvPoint p2 = cvPoint(iNode->getData()->fx, iNode->getData()->fy);
        cvLine(image, p1, p2, cvScalar(0, 255, 0), 1);
        iNode = iNode->getNext();
        cvShowImage("img", image);
        cvWaitKey();
    }
}

void ImageInterpreter::rightAnalizeAux(IplImage* pImage, CvPoint pAreaS, CvPoint pAreaF){
    cout<<"Right A"<<endl;
    
    bool fline = false; //Utilizado para indicar que se ha alcanzado una linea
                        // y que se ha hecho un analisis sobre la primera linea
                        // individual.
    
    line* lastLine = 0; //Puntero a la última linea registrada
    uchar* pointer = (uchar*)pImage->imageData; //Puntero a los datos de la imágen
    
    //Ciclo para recorrer el lado derecho del area de restauración
    
    //En este ciclo se aplica el teorema de la pendiente de una linea pixelada
    //tomando asi la primera linea individual como base y las otras como dependientes
    //de esta.
    for (int y = (pAreaS.y==0?0:pAreaS.y-1);
            y <= (pAreaF.y==pImage->height-1?pImage->height-1:pAreaF.y+1); y++){
        
        //Se valida si existe linea
        if ((pointer+y*pImage->widthStep)[pAreaF.x] == 0){
            
            if (!fline){ //Si no ha habido un primer punto local entonces:
                fline = true; //Levantar la bandera
                
                line* ln = new line; //Crear una linea que sera la base
                lastLine = ln;  //--------^ 
                
                //Definir puntos locales de la linea
                ln->sx = pAreaF.x;
                ln->sy = y;
                
                analizeRight(pImage, ln); //Encontrar punto final o intermedio
                
                _lines->insert(ln); //Insertar la linea en los resultados
                
            } else {
                line* ln = new line; //Crear linea dependiente
                
                //Definir puntos finales
                ln->sx = pAreaF.x; 
                ln->sy = y;
                
                //Según el teorema, definir puntos dependientes o asociados
                ln->fx = lastLine->fx;
                ln->fy = lastLine->fy+1;                
                
                lastLine = ln; //Definirla como linea base para las próximas
                _lines->insert(ln); //Insertar en los resultados
            }
            
        } else {
            fline = false; //Cuando se deje de detectar un punto quiere decir
                           //que se ha acabado la linea y por ende se pueden considerar otras.
        }
        
    }
}

void ImageInterpreter::leftAnalizeAux(IplImage* pImage, CvPoint pAreaS, CvPoint pAreaF){
    /*
     * El algoritmo que aplica este método es el mismo que el que implementa rightAnalizeAux
     * por lo que se pide referenciarse a este ante el analisis del mismo
     */
    cout<<"Left A"<<endl;
    bool fline = false;
    line* lastLine = 0;
    uchar* pointer = (uchar*)pImage->imageData;
    
    for (int y = (pAreaS.y==0?0:pAreaS.y-1);
            y <= (pAreaF.y==pImage->height-1?pImage->height-1:pAreaF.y+1); y++){
        
        if ((pointer+y*pImage->widthStep)[pAreaS.x] == 0){
            
            if (!fline){
                fline = true;
                line* ln = new line;
                lastLine = ln;
                ln->fx = pAreaS.x;
                ln->fy = y;
                analizeLeft(pImage, ln);
                _lines->insert(ln);
                
            } else {
                line* ln = new line;
                ln->fx = pAreaS.x;
                ln->fy = y;
                ln->sx = lastLine->sx;
                ln->sy = lastLine->sy+1;                
                lastLine = ln;
                _lines->insert(ln);
            }
            
        } else {
            fline = false;
        }
    }
}


void ImageInterpreter::bottomAnalizeAux(IplImage* pImage, CvPoint pAreaS, CvPoint pAreaF){
    /*
     * El algoritmo que aplica este método es el mismo que el que implementa rightAnalizeAux
     * por lo que se pide referenciarse a este ante el analisis del mismo
     */
    cout<<"Bottom A"<<endl;
    bool fline = false;
    line* lastLine = 0;
    uchar* pointer = (uchar*)pImage->imageData;
    
    for (int x = (pAreaS.x==0?0:pAreaS.x-1);
            x <= (pAreaF.x==pImage->width-1?pImage->width-1:pAreaF.x+1); x++){
        
        if ((pointer+pAreaF.y*pImage->widthStep)[x] == 0){
            
            if (!fline){
                fline = true;
                line* ln = new line;
                lastLine = ln;
                ln->sx = x;
                ln->sy = pAreaF.y;
                analizeBottom(pImage, ln);
                _lines->insert(ln);
                
            } else {
                line* ln = new line;
                ln->sx = x;
                ln->sy = pAreaF.y;
                ln->fx = lastLine->fx+1;
                ln->fy = lastLine->fy;
                lastLine = ln;
                _lines->insert(ln);
            }
            
        } else {
            fline = false;
        }
        
    }
}

void ImageInterpreter::topAnalizeAux(IplImage* pImage, CvPoint pAreaS, CvPoint pAreaF){
    /*
     * El algoritmo que aplica este método es el mismo que el que implementa rightAnalizeAux
     * por lo que se pide referenciarse a este ante el analisis del mismo
     */
    cout<<"Top A"<<endl;
    bool fline = false;
    line* lastLine = 0;
    uchar* pointer = (uchar*)pImage->imageData;
    
    for (int x = (pAreaS.x==0?0:pAreaS.x-1); 
            x <= (pAreaF.x==pImage->width-1?pImage->width-1:pAreaF.x+1); x++){
        
        if ((pointer+pAreaS.y*pImage->widthStep)[x] == 0){
            
            if (!fline){
                fline = true;
                line* ln = new line;
                lastLine = ln;
                ln->fx = x;
                ln->fy = pAreaS.y;
                analizeTop(pImage, ln);
                _lines->insert(ln);
                
            } else {
                line* ln = new line;
                ln->fx = x;
                ln->fy = pAreaS.y;
                ln->sx = lastLine->sx+1;
                ln->sy = lastLine->sy;                
                lastLine = ln;
                _lines->insert(ln);
            }
            
        } else {
            fline = false;
        }
    }
}

void ImageInterpreter::analizeLeft(IplImage* pImage, line* pLine){
    cout<<"left"<<endl;
    
    //Definimos las posiciones inciales
    int x = pLine->fx; 
    int y = pLine->fy;
    
    bool finish = false; // Variable utilizada para salir del ciclo de analisis
                         // Cuando se encuentra el final de la linea
    int i = 1; 
    
    double tmpSlope = 0; //Será utilizada para almacenar una pendiente temporal
                         //Que servirá para determinar los posibles movimientos
                         //A realizar
    
    int prevMov = -1; //Será utilizada para almacenar el movimiento anterior al
                      //actual, esto para no entrar en un ciclo infinito o no
                      //efectivo de movimiento y regresión
    
    for (i; !finish && i <= RANGE; i++){
        
        if (i == TEMP_SLOPE1 || i == TEMP_SLOPE2){ //Segun la cantidad de 
                                                   //iteraciones se obtendran 
                                                   //dos pendientes temporales
            
            tmpSlope = getSlope(x, y, pLine->fx, pLine->fy);
        }
        
        //Realizar los movimientos pertinentes para alcanzar el final/inicio de la linea
        if (canMove(pImage, UP, x, y) && tmpSlope <= 0 && prevMov != DOWN){
            y--;        
            prevMov = UP;
            
        } else if (canMove(pImage, UPPER_LEFT, x, y) && tmpSlope <= 0){
            x--;
            y--;
            prevMov = UPPER_LEFT;
            
        } else if (canMove(pImage, LEFT, x, y)){
            x--;
            prevMov = LEFT;
            
        } else if (canMove(pImage, LOWER_LEFT, x, y) && tmpSlope >= 0){
            x--;
            y++;
            prevMov = LOWER_LEFT;
            
        } else if (canMove(pImage, DOWN, x, y) && tmpSlope >= 0 && prevMov != UP){
            y++;
            prevMov = DOWN;
            
        } else {
            finish = true;
        }
    }
    //Definir los puntos faltantes de la linea
    pLine->sx = x;
    pLine->sy = y;
    cout<<"f left"<<endl;
}

void ImageInterpreter::analizeRight(IplImage* pImage, line* pLine){
    /*
     * El algoritmo que aplica este método es el mismo que el que implementa analizeLeft
     * por lo que se pide referenciarse a este ante el analisis del mismo
     */
    cout<<"right"<<endl;
    int x = pLine->sx;
    int y = pLine->sy;
    bool finish = false;
    int i = 1;
    double tmpSlope = 0;
    int prevMov = -1;
    
    for (i; !finish && i <= RANGE; i++){        
        
        if (i == TEMP_SLOPE1 || i == TEMP_SLOPE2){
            tmpSlope = getSlope(pLine->sx, pLine->sy, x, y);
        }
        
        if (canMove(pImage, UP, x, y) && tmpSlope >= 0 && prevMov != DOWN){
            y--;
            prevMov = UP;
            
            
        } else if (canMove(pImage, UPPER_RIGHT, x, y) && tmpSlope >= 0){
            x++;
            y--;
            prevMov = UPPER_RIGHT;
            
        } else if (canMove(pImage, RIGHT, x, y)){
            x++;
            prevMov = RIGHT;
            
        } else if (canMove(pImage, LOWER_RIGHT, x, y) && tmpSlope <= 0){
            x++;
            y++;
            prevMov = LOWER_RIGHT;
            
        } else if (canMove(pImage, DOWN, x, y)  && tmpSlope <= 0 && prevMov != UP){
            y++;
            prevMov = DOWN;
            
        } else {
            finish = true;
        }
    }
    
    pLine->fx = x;
    pLine->fy = y;
    cout<<"f right"<<endl;
}

void ImageInterpreter::analizeBottom(IplImage* pImage, line* pLine){
    /*
     * El algoritmo que aplica este método es el mismo que el que implementa analizeLeft
     * por lo que se pide referenciarse a este ante el analisis del mismo
     */
    cout<<"bottom"<<endl;
    int x = pLine->sx;
    int y = pLine->sy;
    bool finish = false;
    int i = 1;
    double tmpSlope = 0;
    int prevMov = -1;
    
    for (i; !finish && i <= RANGE; i++){
        
        if (i == TEMP_SLOPE1 || i == TEMP_SLOPE2){
            tmpSlope = getSlope(pLine->sx, pLine->sy, x, y);
        }
        
        if (canMove(pImage, LEFT, x, y) && tmpSlope >= 0 && prevMov != RIGHT){
            x--;
            prevMov = LEFT;
            cout<<"l"<<endl;
            
        } else if (canMove(pImage, LOWER_LEFT, x, y) && tmpSlope >= 0){
            x--;
            y++;
            prevMov = LOWER_LEFT;
            
        } else if (canMove(pImage, DOWN, x, y)){
            y++;
            prevMov = DOWN;
            
        } else if (canMove(pImage, LOWER_RIGHT, x, y) && tmpSlope <= 0){
            y++;
            x++;
            prevMov = LOWER_RIGHT;
            
        } else if (canMove(pImage, RIGHT, x, y) && tmpSlope <= 0 && prevMov != LEFT){
            x++;
            prevMov = RIGHT;
            
        } else {
            finish = true;
        }
    }
    
    pLine->fx = x;
    pLine->fy = y;
    cout<<"f bottom"<<endl;
}

void ImageInterpreter::analizeTop(IplImage* pImage, line* pLine){
    /*
     * El algoritmo que aplica este método es el mismo que el que implementa analizeLeft
     * por lo que se pide referenciarse a este ante el analisis del mismo
     */
    cout<<"top"<<endl;
    int x = pLine->fx;
    int y = pLine->fy;
    bool finish = false;
    int i = 1;
    double tmpSlope = 0;
    int prevMov = -1;
    
    for (i; !finish && i <= RANGE; i++){
        
        if (i == TEMP_SLOPE1 || i == TEMP_SLOPE2){
            tmpSlope = getSlope(x, y, pLine->fx, pLine->fy);
        }
        
        if (canMove(pImage, LEFT, x, y) && tmpSlope <= 0 && prevMov != RIGHT){
            x--;
            prevMov = LEFT;
            
        } else if (canMove(pImage, UPPER_LEFT, x, y) && tmpSlope <= 0){
            x--;
            y--;
            prevMov = UPPER_LEFT;
            
        } else if (canMove(pImage, UP, x, y)){
            y--;
            prevMov = UP;
            
        } else if (canMove(pImage, UPPER_RIGHT, x, y) && tmpSlope >= 0){
            y--;
            x++;
            prevMov = UPPER_RIGHT;
            
        } else if (canMove(pImage, RIGHT, x, y) && tmpSlope >= 0 && prevMov != LEFT){
            x++;
            prevMov = RIGHT;
            
        } else {
            finish = true;
        }
    }
    pLine->sx = x;
    pLine->sy = y;
    cout<<"f top"<<endl;
}

double ImageInterpreter::getSlope(double pxi, double pyi, double pxf, double pyf){
    /*
     * El algoritmo que aplica este método es el mismo que el que implementa analizeLeft
     * por lo que se pide referenciarse a este ante el analisis del mismo
     */
    if (pxf==pxi){
        return 0;
    } else {
        return -1*(pyf-pyi)/(pxf-pxi);
    }    
}

bool ImageInterpreter::canMove(IplImage* pImage, int pDirection, int px, int py){
    /*
     * Se valida según sea el caso si el pixel a moverse es parte o no de la linea
     */
    switch (pDirection){
        case LEFT:
            if (px == 0){ 
                return false;
            } else {
                return ((uchar*)(pImage->imageData+py*pImage->widthStep))[px-1] == 0;
            }
            
        case UPPER_LEFT:
            if (px == 0 || py == 0){
                return false;
            } else {
                return ((uchar*)(pImage->imageData+(py-1)*pImage->widthStep))[px-1] == 0;
            }
            
        case UP:
            if (py == 0){
                return false;
            } else {
                return ((uchar*)(pImage->imageData+(py-1)*pImage->widthStep))[px] == 0;
            }
            
        case UPPER_RIGHT:
            if (py == 0 || px == pImage->width-1){
                return false;
            } else {
                return ((uchar*)(pImage->imageData+(py-1)*pImage->widthStep))[px+1] == 0;
            }
            
        case RIGHT:
            if (px == pImage->width-1){
                return false;
            } else {
                return ((uchar*)(pImage->imageData+py*pImage->widthStep))[px+1] == 0;
            }
            
        case LOWER_RIGHT:
            if (px == pImage->width-1 || py == pImage->height-1){
                return false;
            } else {
                return ((uchar*)(pImage->imageData+(py+1)*pImage->widthStep))[px+1] == 0;
            }
            
        case DOWN:
            if (py == pImage->height-1) {
                return false;
            } else{
                return ((uchar*)(pImage->imageData+(py+1)*pImage->widthStep))[px] == 0;
            }
            
        case LOWER_LEFT:
            if (px == 0 || py == pImage->height-1){
                return false;
            } else {
                return ((uchar*)(pImage->imageData+(py+1)*pImage->widthStep))[px-1] == 0;
            }
        default:
            return false;
    }
}