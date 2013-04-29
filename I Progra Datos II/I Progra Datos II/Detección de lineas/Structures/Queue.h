/* 
 * File:   Queue.h
 * Author: joseph
 *
 * Created on 3 de abril de 2013, 03:40 PM
 */

#ifndef QUEUE_H
#define	QUEUE_H

#include "ListNode.h"
#include <iostream>
using namespace std;

template <class t>
class Queue {
public:
    Queue();
    ~Queue();
    
    void printMe();
    void enqueue(t* pData);
    t* dequeue();
    t* top();
    t* bottom() const {return _bottom->getData();}
    bool inQueue(t* pData);
    
private:
    ListNode<t>* _top;
    ListNode<t>* _bottom;
};

#endif	/* QUEUE_H */

template <class t>
Queue<t>::Queue() {
    _top = _bottom = 0;
}

template <class t>
Queue<t>::~Queue() {
    ListNode<t>* iNode = _top;
    while (iNode != 0){
        ListNode<t>* next = iNode->getNext();
        delete iNode;
        iNode = next;
    }
}

template <class t>
void Queue<t>::printMe(){
    ListNode<t>* iNode = _top;
    while (iNode != 0){
        cout<<"("<<iNode->getX()<<", "<<iNode->getY()<<endl;
        iNode = iNode->getNext();
    }
}

template <class t>
void Queue<t>::enqueue(t* pData){
    ListNode<t>* newNode = new ListNode<t>(pData);
    if (_top == 0){
        _top = _bottom = newNode;
    } else {
        newNode->setPrevious(_bottom);
        _bottom->setNext(newNode);
        _bottom = newNode;
    }
}

template <class t>
t* Queue<t>::dequeue(){
    if (_top == 0){
        return 0;
    }
    if (_top == _bottom){
        ListNode<t>* temp = _top;
        _top = _bottom = 0;
        return temp;
    } else {
        ListNode<t>* temp = _top;
        _top = _top->getNext();
        _top->setPrevious(0);
        return temp->getData();
    }
}

template <class t>
t* Queue<t>::top(){
    return _top->getData();
}

template <class t>
bool Queue<t>::inQueue(t* pData){
    ListNode<t>* iNode = _top;
    while (iNode != 0 && *iNode->getData() != *pData){
        iNode = iNode->getNext();
    }
    return iNode!=0;
}
