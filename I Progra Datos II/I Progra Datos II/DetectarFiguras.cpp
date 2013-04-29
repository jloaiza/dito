#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <unistd.h>
#include <iostream>
#include "CoordenadasGeometricas.h"
#include "DetectarFigurasImage.h"

using namespace std;

#ifndef FIGURA
#define FIGURA

struct Figura 
{
    int _id, _vertices, _RED, _GREEN, _BLUE;
    const char * _nombre;
};

#endif

CoordenadasGeometricas* _listaCoordenadas = new CoordenadasGeometricas();

Figura _cuadrado = {1, 4, 255, 0, 0, "cuadrado"};
Figura _triangulo = {2, 3, 255, 255, 0, "triangulo"};
Figura _pentagono = {3, 5, 255, 0, 255, "pentagono"};
Figura _octagono = {4, 8, 0, 0, 255, "octagono"};
Figura _decagono = {5, 10, 0, 255, 255, "decagono"};
Figura _figuras[5] = {_cuadrado, _triangulo, _pentagono, _octagono, _decagono};


Figura FiguraGenerica(int pVertices) 
{
    for (int x=0; x < int(sizeof _figuras/sizeof(Figura)) ; x++) 
    {
        if ( ( (Figura)_figuras[x] )._vertices == pVertices ) 
        {
            Figura temp = _figuras[x];
            return temp;
        }
    }
    Figura temp = {0,0,0,0,0}; 
    return temp;	
}

/**
 * detecta cuadros, triangulos
 * @param pParalelogramo puntero a la imagen en tiempo real, que recibe la camara
 * @version 1.0
 */
IplImage* DetectarParalelogramos(IplImage* pParalelogramo) 
{
    /* Estructura de bajo nivel que almacena cantidades crecientes de datos */
    CvMemStorage* paralelogramoMemory = cvCreateMemStorage(0);

    /* */
    CvFont Letra;
    cvInitFont( &Letra, CV_FONT_VECTOR0, 0.5, 0.5, 0, 0.5, CV_AA);

    /* almacenan las secuencias de pixeles que definen los contornos */
    CvSeq* Contornos;
    CvSeq* Resultado;

    /* */
    IplImage* CopiaParalelogramo = cvCloneImage(pParalelogramo);

    /* imagen en gris para detectar contornos */
    IplImage* DibujoParalelogramo = cvCreateImage( cvSize(CopiaParalelogramo->width, CopiaParalelogramo->height), IPL_DEPTH_8U, 1);

    /* convierte la imagen de entrada de un color a otro */
    cvCvtColor(CopiaParalelogramo, DibujoParalelogramo, CV_BGR2GRAY);

    /* aplica un umbral fijo a una matriz de un solo canal */
    cvThreshold(DibujoParalelogramo, DibujoParalelogramo, 50, 255, CV_THRESH_BINARY);

    cvSmooth(DibujoParalelogramo, DibujoParalelogramo, CV_GAUSSIAN ,3, 3);

    /* encuentra los bordes en la imagen de entrada y los marca en la imagen de salida */
    cvCanny(DibujoParalelogramo, DibujoParalelogramo, 50, 150, 3);

    /* recupera el numero de contornos de la imagen binaria y retorna el numero de contornos recuperados */
    cvFindContours(DibujoParalelogramo, paralelogramoMemory, &Contornos, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
    
    while (Contornos) 
    {
        /* se aproximan una o mas curvas y le asigna a result la cantidad de aproximaciones */
        Resultado = cvApproxPoly(Contornos, sizeof(CvContour), paralelogramoMemory, CV_POLY_APPROX_DP, cvContourPerimeter(Contornos)*0.02, 0);

	/* podemos entender las aproximaciones como la cantidad de vertices que unió */

        if (fabs( cvContourArea(Resultado, CV_WHOLE_SEQ) ) > 30) 
        {
            CvPoint* pt[Resultado->total];
            for (int i = 0; i < Resultado->total ; i++) 
            {
                pt[i] = (CvPoint*) cvGetSeqElem(Resultado, i);
            }                
            for (int j = 0; j < Resultado->total; j++) 
            {
                Figura temporal = FiguraGenerica(Resultado->total);
                if (temporal._nombre==0) { }
                else 
                {
                    if (j < Resultado->total-1) { cvLine(CopiaParalelogramo, *pt[j], *pt[j+1], CV_RGB(temporal._RED, temporal._GREEN, temporal._BLUE)); }
                    else 
                    { 
                        cvLine(CopiaParalelogramo, *pt[j], *pt[0], CV_RGB(temporal._RED, temporal._GREEN, temporal._BLUE)); 
                        CvPoint pt1;
                        pt1.x = (*pt[0]).x;
                        pt1.y = (*pt[0]).y;
                        if(!_listaCoordenadas->BuscarCordenada(_listaCoordenadas->_lista,pt1.x,pt1.y))
                        {
                            _listaCoordenadas->InsertarCoordenada(&_listaCoordenadas->_lista,pt1.x,pt1.y);
                            cout << "X: " << pt1.x << " Y: " << pt1.y << endl;
                        }
                        cvPutText(CopiaParalelogramo, temporal._nombre , pt1, &Letra,CV_RGB(temporal._RED, temporal._GREEN, temporal._BLUE) );
                    }	
                }					
            }
        }		
        Contornos = Contornos->h_next;	
    }
    
    cvReleaseImage(&DibujoParalelogramo);
    cvReleaseMemStorage(&paralelogramoMemory);
    //sleep(1);
    
    return CopiaParalelogramo;	
}

IplImage* DetectarCirculos(IplImage* pCirculo)
{
    CvFont Letra;
    CvPoint Punto;
    
    CvMemStorage* circleMemory = cvCreateMemStorage(0);
    
    cvInitFont(&Letra, CV_FONT_VECTOR0, 0.5, 0.5, 0, 0.1, CV_AA);
    
    IplImage* CopiaCirculo = cvCreateImage(cvGetSize(pCirculo), IPL_DEPTH_8U, 1);    
    IplImage* DibujoCirculo = cvCreateImage(cvGetSize(CopiaCirculo), CopiaCirculo->depth, 3);
    
    cvCvtColor(pCirculo, CopiaCirculo, CV_BGR2GRAY);
    
    cvThreshold(CopiaCirculo,CopiaCirculo,70,255,CV_THRESH_BINARY);
    
    cvSmooth(CopiaCirculo,CopiaCirculo,CV_GAUSSIAN,11,11);

    cvCanny(CopiaCirculo,CopiaCirculo,100,150,3);
    
    CvSeq* TotalCirculos = cvHoughCircles(CopiaCirculo, circleMemory, CV_HOUGH_GRADIENT, 1, pCirculo->height/2, 100, 55);
   
    cvSetZero(DibujoCirculo);
    
    for (size_t i = 0; i < TotalCirculos->total; i++)
    {
        float* p = (float*)cvGetSeqElem(TotalCirculos, i); 
        cv::Point center(cvRound(p[0]), cvRound(p[1]));
        int Radio = cvRound(p[2]);
        cvCircle(DibujoCirculo, center, Radio, CV_RGB(0,255,0), 2, 4, 0 );
        Punto.x = center.x-20;
        Punto.y = center.y+5;
        cvPutText(DibujoCirculo, "Circulo", Punto, &Letra,CV_RGB(0,255,0) );
    } 
    CvSeq* Contornos = 0;
    cvCvtColor(DibujoCirculo, CopiaCirculo, CV_BGR2GRAY);   
    cvSetZero(DibujoCirculo);
    DibujoCirculo = cvCloneImage(pCirculo);
    
    cvFindContours(CopiaCirculo, circleMemory, &Contornos, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
    
    for (;Contornos != 0; Contornos = Contornos->h_next)
    {
        CvScalar Color = CV_RGB( 0, 255, 0 );
        cvDrawContours(DibujoCirculo, Contornos, Color, CV_RGB(0,0,0), -1, CV_FILLED, 8, cvPoint(0,0));
    }
     
   
    cvReleaseImage(&CopiaCirculo);
    cvReleaseMemStorage(&circleMemory);
    
    return DibujoCirculo;
}

int main(int argc, char **argv) 
{
            
    CvCapture* capture = cvCaptureFromCAM(0);

    if (!capture) 
    { 
        fprintf( stderr, "ERROR \n");
        getchar();
        return -1;
    }
    
    bool captured = false;

    while (captured == false) 
    {	
        IplImage* src = cvQueryFrame( capture );
        IplImage* csrc = NULL;
        if(!src) 
        {
            fprintf(stderr, "ERROR \n" );
            getchar();
            break;
        }
        
        csrc = DetectarCirculos(src); 
        //csrc = DetectarParalelogramos(src);
        cvShowImage("Detecciones Geométricas", csrc); 
        cvReleaseImage(&csrc);   

        if ( (cvWaitKey(10) & 255) == 27 ) break;
    }

    cvReleaseCapture (&capture);
    cvDestroyAllWindows(); 
    cvWaitKey(0);
    return 0;
}

