#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Thread {
public:
    /**
     * Method who start the thread.
     */
    void start();
    
    /**
     * Get the basic thread object.
     * @return 
     */
    inline pthread_t getThread() const{
        return _thread;
    }
    
    /**
     * This method have to be overriden with the code to excecute the thread.
     * @return 
     */
    virtual void* run(){return 0;}
private:
    pthread_t _thread;
    
    /**
     * Static method to call the run method. This is used because pThread class 
     * can't run class methods.
     * @param pObject
     * @return 
     */
    inline static void* callRun(void* pObject){
        ((Thread*)pObject)->run();
        return (void*)0;
    }
    
};

#endif  /* THREAD_H */