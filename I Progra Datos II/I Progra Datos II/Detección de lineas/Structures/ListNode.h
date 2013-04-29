/* 
 * File:   ListNode.h
 * Author: joseph
 *
 * Created on 3 de abril de 2013, 12:59 PM
 */

#ifndef LISTNODE_H
#define	LISTNODE_H


template <class t>
class ListNode {
public:
    ListNode(int pX, int pY);
    ListNode(t* pPoint);
    ListNode();
    
    ListNode<t>* getNext() const {return _next;}
    void setNext(ListNode<t>* pNext) { _next = pNext;}
    ListNode<t>* getPrevious() const {return _previous;}
    void setPrevious(ListNode<t>* pPrevious) { _previous = pPrevious;}
    int getX() const {return _x;}
    void setX(int pX){ _x = pX;}
    int getY() const {return _y;}
    void setY(int pY){ _y = pY;}
    t* getData() const {return _data;}
    void setData(t* pPoint){_data = pPoint;}
    
private:
    ListNode* _next;
    ListNode* _previous;
    int _x;
    int _y;
    t* _data;
};



template <class t>
ListNode<t>::ListNode(t* pPoint){
    _data = pPoint;
}

template <class t>
ListNode<t>::ListNode(int pX, int pY) {
    _next = 0;
    _previous = 0;
    _x = pX;
    _y = pY;
}

template <class t>
ListNode<t>::ListNode(){
    ListNode(0, 0);
}

#endif	/* LISTNODE_H */