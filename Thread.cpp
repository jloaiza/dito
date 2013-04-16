/* 
 * File:   Thread.cpp
 * Author: joseph
 * 
 * Created on 2 de marzo de 2013, 02:49 PM
 */

#include "Thread.h"

void Thread::start(){
    pthread_attr_t attrib;
    pthread_attr_init(&attrib);
    pthread_attr_setdetachstate(&attrib, PTHREAD_CREATE_JOINABLE);
    pthread_create(&_thread, &attrib, callRun, (void*)this);
    pthread_attr_destroy(&attrib);
}