/* 
 * File:   main.cpp
 * Author: joseph
 *
 * Created on 26 de abril de 2013, 12:37 AM
 */

#include <cstdlib>

#include "ImageInterpreter.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    ImageInterpreter* n = new ImageInterpreter();
    n->analize("/home/joseph/Giskard/Images/line.jpg", cvPoint(150, 0), cvPoint(200, 400));
    //n->analize("/home/joseph/Giskard/Images/line.jpg", cvPoint(0, 200), cvPoint(500, 300));
    return 0;
}

