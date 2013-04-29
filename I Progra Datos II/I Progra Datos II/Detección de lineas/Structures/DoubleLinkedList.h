/* 
 * File:   DoubleLinkedList.h
 * Author: joseph
 *
 * Created on 3 de abril de 2013, 07:59 PM
 */

#ifndef DOUBLELINKEDLIST_H
#define	DOUBLELINKEDLIST_H

#include "ListNode.h"

template <class t>
class DoubleLinkedList {
public:
    DoubleLinkedList();
    ~DoubleLinkedList();
    void insert(t* pData);
    void erase(t* pData);
    t* search(t* pData);
    bool isInList(t* pData);
    ListNode<t>* getHead(){
        return _head;
    }
    
private:
    ListNode<t>* _head;
    ListNode<t>* _tail;
};

#endif	/* DOUBLELINKEDLIST_H */


template <class t>
DoubleLinkedList<t>::DoubleLinkedList() {
    _head = _tail = 0;
}

template <class t>
DoubleLinkedList<t>::~DoubleLinkedList() {
    
}

template <class t>
void DoubleLinkedList<t>::insert(t* pData){
    ListNode<t>* newNode = new ListNode<t>(pData);
    if (_head == 0){
        _head = _tail = newNode;
    } else {
        _tail->setNext(newNode);
        newNode->setPrevious(_tail);
        _tail = newNode;
    }
}

template <class t>
void DoubleLinkedList<t>::erase(t* pData){
    if (_head != 0){
        ListNode<t>* iNode = _head;
        while (iNode != 0 && *iNode->getData() != *pData){
            iNode = iNode->getNext();
        }
        if (iNode != 0){
            if (iNode == _head){                
                if (_head != _tail){
                    _head->getNext()->setPrevious(0);
                    _head = _head->getNext();
                } else {
                    _head = _tail = 0;
                }
            } else if (iNode == _tail){
                _tail->getPrevious()->setNext(0);
                _tail = _tail->getPrevious();
            } else {
                iNode->getPrevious()->setNext(iNode->getNext());
                iNode->getNext()->setPrevious(iNode->getPrevious());
            }
        }
    }
}

template <class t>
t* DoubleLinkedList<t>::search(t* pData){
    ListNode<t>* iNode = _head;
    while (iNode != 0 && *iNode->getData() != *pData){
        iNode = iNode->getNext();
    }
    return iNode;
}


template <class t>
bool DoubleLinkedList<t>::isInList(t* pData){
    ListNode<t>* iNode = _head;
    while (iNode != 0 && *iNode->getData() != *pData){
        iNode = iNode->getNext();
    }
    return iNode != 0;
}