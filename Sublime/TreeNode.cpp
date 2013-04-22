#include "TreeNode.h"

template <class t>
bool TreeNode<t>::isRightSon() const {
	if (_parent != 0){
		if (_parent->getRightChild == this){
			return true
		}
	}
	return false;
}

template <class t>
bool TreeNode<t>::isLeftSon() const {
	if (_parent != 0){
		if (_parent->getLeftChild == this){
			return true
		}
	}
	return false;
}

template <class t>
bool TreeNode<t>::isLeaf() const {
	return _leftChild == 0 && _rightChild == 0;
}

template <class t>
bool TreeNode<t>::haveBothChilds() const {
	return _leftChild != 0 && _rightChild != 0;
}