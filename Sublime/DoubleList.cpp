#include "DoubleList.h"

void DoubleList::insertDecrescent(t* pData){
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

void DoubleList::insertCrescent(t* pData){
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

void DoubleList::insertLinear(t* pData){
	ListNode* newNode = new ListNode(pData);
	if(_head == 0){
		_head = _tail = newNode;
	} else {
		_tail.setNext(newNode);
		newNode.setPrevious(_tail);
		_tail = newNode;
	}
}

void DoubleList::insert(t* pData){
	if (_type == LINEAR_LIST){
		insertLinear(pData);
	} else if (_type == DECRESCENT_LIST){
		insertDecrescent(pData);
	} else if (_type == CRESCENT_LIST){
		insertCrescent(pData);
	}
}

ListNode* DoubleList::searchAux(t* pData){
	ListNode* iNode = _head;
	while (iNode != 0 && iNode->getData() != pData){
		iNode = iNode->getNext();
	}
	return iNode;
}

t* DoubleList::search(t* pData){
	ListNode* searched = searchAux(pData);
	if (searched != 0){
		return searched->getData();
	} else {
		return 0;
	}
}

t* DoubleList::erase(t* pData){
	ListNode* toErase = searchAux(pData);
	if (toErase != 0){
		toErase->getPrevious()->setNext(toErase->getNext());
		toErase->getNext()->setPrevious(toErase->getPrevious);
		return toErase->getData();
	} else {
		return 0;
	}
}