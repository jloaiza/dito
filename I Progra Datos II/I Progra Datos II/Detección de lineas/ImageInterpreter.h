/**
* Author: Joseph
*/

#ifndef IMAGE_INTERPRETER
#define IMAGE_INTERPRETER

#include <highgui.h>
#include <cv.h>
#include <stdlib.h>
#include "structures/DoubleLinkedList.h"
#include "structures/Queue.h"

class ImageInterpreter {
    
public:
    /**
     * Initializer.
     */
    ImageInterpreter();
    
    struct line{
        int sx;
        int sy;
        int fx;
        int fy;
    };
    
    
    /**
     * Method to analize a picture and get it indiviudal lines of it.
     * This method stores the results in an internal list that you can acces
     * with the getLinesList method. If you want to analize the image again or
     * a new one, you have to initializate a new ImageInterpreter.
     * 
     * @param pPath Path to the image
     * @param pAreaS First point of the restoration area
     * @param pAreaF Last point of the restoration area
     */
    void analize(char* pPath, CvPoint pAreaS, CvPoint pAreaF);
    
    /**
     * This method returns the head of the list that stores the results.
     * 
     * @return 
     */
    ListNode<line>* getLinesList() const{
        return _lines->getHead();
    }
private:
    
    static const int LEFT = 0;
    static const int UPPER_LEFT = 1;
    static const int UP = 2;
    static const int UPPER_RIGHT = 3;
    static const int RIGHT = 4;
    static const int LOWER_RIGHT = 5;
    static const int DOWN = 6;
    static const int LOWER_LEFT = 7;    
    
    /**
     * This method analize the top region of the restoration area in search of
     * lines.
     * 
     * @param pImage Image to analize, this image most be a binary image of only one channel
     * @param pAreaS First point of the restoration area
     * @param pAreaF Last point of the restoration area
     */
    void topAnalizeAux(IplImage* pImage, CvPoint pAreaS, CvPoint pAreaF);
    
    /**
     * This method analize the bottom region of the restoration area in search of
     * lines.
     * 
     * @param pImage Image to analize, this image most be a binary image of only one channel
     * @param pAreaS First point of the restoration area
     * @param pAreaF Last point of the restoration area
     */
    void bottomAnalizeAux(IplImage* pImage, CvPoint pAreaS, CvPoint pAreaF);
    
    /**
     * This method analize the left region of the restoration area in search of
     * lines.
     * 
     * @param pImage Image to analize, this image most be a binary image of only one channel
     * @param pAreaS First point of the restoration area
     * @param pAreaF Last point of the restoration area
     */
    void leftAnalizeAux(IplImage* pImage, CvPoint pAreaS, CvPoint pAreaF);
    
    /**
     * This method analize the right region of the restoration area in search of
     * lines.
     * 
     * @param pImage Image to analize, this image most be a binary image of only one channel
     * @param pAreaS First point of the restoration area
     * @param pAreaF Last point of the restoration area
     */
    void rightAnalizeAux(IplImage* pImage, CvPoint pAreaS, CvPoint pAreaF);
    
    /**
     * This method returns the slope of a line.
     * 
     * @param pxi Position on X axis of the first point
     * @param pyi Position on Y axis of the first point
     * @param pxf Position on X axis of the second point
     * @param pyf Position on Y axis of the second point
     * @return a double that represent the slope
     */
    double getSlope(double pxi, double pyi, double pxf, double pyf);
    
    /**
     * This function return if the point in the specified direction its black,
     * it is, if the point in the direction is part of the line so you can
     * "move" to it or not.
     * 
     * @param pImage Image to analize, this image most be a binary image of only one channel
     * @param pDirection Constant of ImageInerpreter that tells the direction
     * @param px Actual position
     * @param py Actual position
     * @return 
     */
    bool canMove(IplImage* pImage, int pDirection, int px, int py);
    
    
    /**
     * Analize a single line at the top region of the restoration area,
     * is use by topAnalizeAux method. It stores the missing point in the line struct
     * 
     * @param pImage Image to analize, this image most be a binary image of only one channel
     * @param pLine Line struct that contains the final point of the line
     */
    void analizeTop(IplImage* pImage, line* pLine);
    
    /**
     * Analize a single line at the bottom region of the restoration area,
     * is use by bottomAnalizeAux method. It stores the missing point in the line struct
     * 
     * @param pImage Image to analize, this image most be a binary image of only one channel
     * @param pLine Line struct that contains the initial point of the line
     */
    void analizeBottom(IplImage* pImage, line* pLine);
    
    /**
     * Analize a single line at the left region of the restoration area,
     * is use by leftAnalizeAux method. It stores the missing point in the line struct
     * 
     * @param pImage Image to analize, this image most be a binary image of only one channel
     * @param pLine Line struct that contains the final point of the line
     */
    void analizeLeft(IplImage* pImage, line* pLine);
    
    /**
     * Analize a single line at the bottom region of the restoration area,
     * is use by rightAnalizeAux method. It stores the missing point in the line struct
     * 
     * @param pImage Image to analize, this image most be a binary image of only one channel
     * @param pLine Line struct that contains the initial point of the line
     */
    void analizeRight(IplImage* pImage, line* pLine);
    
    DoubleLinkedList<line>* _lines; //List that contains the present lines in th image
    
};

#endif /* data */