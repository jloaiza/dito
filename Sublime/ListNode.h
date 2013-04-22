/*

Author: Joseph Loaiza

*/

#ifndef LIST_NODE
#define LIST_NODE

template <class t>
class ListNode{
private:
	t* _data;
	ListNode* _next;
	ListNode* _previous;
public:
	ListNode(t* pData){
		_data = pData;
		_next = _previous = 0;
	}

	t* getData() const {
		return _data;
	}

	ListNode* getNext() const {
		return _next;
	}

	ListNode* getPrevious() const {
		return _previous;
	}

	void setData(t* pData){
		_data = pData;
	}

	void setNext(ListNode* pNode){
		_next = pNode;
	}

	void setPrevious(ListNode* pNode){
		_previous = pNode;
	}
};

#endif /* LIST_NODE */