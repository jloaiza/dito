#ifndef DOUBLE_LIST
#define DOUBLE_LIST

#include "ListNode.h"

template <class t>
class DoubleList{
private:
	ListNode<t>* _head;
	ListNode<t>* _tail;
	int _type;

	void insertDecrescent(t* pData);
	void insertCrescent(t* pData);
	void insertLinear(t* pData);
	ListNode<t>* searchAux(t* pData);

public:
	DoubleList(int pType){
		_type = pType;
		_head = _tail = 0;
	}

	static const int LINEAR_LIST = 0;
	static const int DECRESCENT_LIST = 1;
	static const int CRESCENT_LIST = 2;

	void insert(t* pData);
	t* erase(t* pData);
	t* search(t* pData);

	ListNode<t>* getHead() const{
		return _head;
	}
};

#endif /*DOUBLE_LIST*/

//-------------------------------------Aqui empieza la definición de los métodos -----------------------------------
template <class t>
void DoubleList<t>::insertDecrescent(t* pData){
	ListNode* newNode = new ListNode(pData);
	if (_head == 0){
		_head = _tail = newNode;
	} else {
		if (newNode->getData() > _head->getData()){
			newNode->setNext(_head);
			_head->setPrevious(newNode);
			_head = newNode;
		} else if (newNode->getData() < _tail->getData){
			_tail->setNext(newNode);
			newNode->setPrevious(_tail);
			_tail = newNode;
		} else {
			ListNode* iNode = _head;
			while (iNode != 0 && newNode->getData() < iNode->getData()){
				iNode = iNode->getNext();
			}
			if (iNode != 0){
				newNode->setPrevious(iNode);
				newNode->setNext(iNode->getNext());
				iNode->getNext()->setPrevious(newNode);
				iNode->setNext(newNode);
			}
		}
	}
}

template <class t>
void DoubleList<t>::insertCrescent(t* pData){
	ListNode* newNode = new ListNode(pData);
	if (_head == 0){
		_head = _tail = newNode;
	} else {
		if (newNode->getData() < _head->getData()){
			newNode->setNext(_head);
			_head->setPrevious(newNode);
			_head = newNode;
		} else if (newNode->getData() > _tail->getData()){
			_tail->setNext(newNode);
			newNode->setPrevious(_tail);
			_tail = newNode;
		} else {
			ListNode* iNode = _head;
			while (iNode != 0 && newNode.getData() > iNode.getData()){
				iNode = iNode->getNext();
			}
			if (iNode != 0){
				newNode->setPrevious(iNode);
				newNode->setNext(iNode->getNext());
				iNode->getNext()->setPrevious(newNode);
				iNode->setNext(newNode);
			}
		}
	}
}

template <class t>
void DoubleList<t>::insertLinear(t* pData){
	ListNode* newNode = new ListNode(pData);
	if(_head == 0){
		_head = _tail = newNode;
	} else {
		_tail.setNext(newNode);
		newNode.setPrevious(_tail);
		_tail = newNode;
	}
}

template <class t>
void DoubleList<t>::insert(t* pData){
	if (_type == LINEAR_LIST){
		insertLinear(pData);
	} else if (_type == DECRESCENT_LIST){
		insertDecrescent(pData);
	} else if (_type == CRESCENT_LIST){
		insertCrescent(pData);
	}
}

template <class t>
ListNode* DoubleList<t>::searchAux(t* pData){
	ListNode* iNode = _head;
	while (iNode != 0 && iNode->getData() != pData){
		iNode = iNode->getNext();
	}
	return iNode;
}

template <class t>
t* DoubleList<t>::search(t* pData){
	ListNode* searched = searchAux(pData);
	if (searched != 0){
		return searched->getData();
	} else {
		return 0;
	}
}

template <class t>
t* DoubleList<t>::erase(t* pData){
	ListNode* toErase = searchAux(pData);
	if (toErase != 0){
		toErase->getPrevious()->setNext(toErase->getNext());
		toErase->getNext()->setPrevious(toErase->getPrevious);
		return toErase->getData();
	} else {
		return 0;
	}
}