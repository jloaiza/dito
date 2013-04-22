#include "AdjacencyNode.h"

#include <iostream>
using namespace std;

void AdjacencyNode::NCRAuxAbove(int pID, int pPosition){
	ConnexionNode* newConnexion = new ConnexionNode(pID);
	if (_aboveConnexions == 0){
		_aboveConnexions = new AVLTree<ConnexionNode>();
		_aboveConnexions->insert(newConnexion);
	} else {
		ConnexionNode* searched = _aboveConnexions->search(newConnexion);
		if (searched == 0){
			_aboveConnexions->insert(newConnexion);
		} else {
			searched->newConnexionRegister();
			if (_aboveMinor == 0 || (_aboveMinor != searched && _aboveMinor->getWeight() >= searched->getWeight())){
				_aboveMinor = searched;
			}
			delete newConnexion;
		}
	}
}

void AdjacencyNode::NCRAuxBottom(int pID, int pPosition){
	ConnexionNode* newConnexion = new ConnexionNode(pID);

	cout<<"NC-B"<<endl;

	if (_bottomConnexions == 0){

		cout<<"BC = 0"<<endl;

		_bottomConnexions = new AVLTree<ConnexionNode>();
		_bottomConnexions->insert(newConnexion);
	} else {

		cout<<"BC != 0"<<endl;

		ConnexionNode* searched = _bottomConnexions->search(newConnexion);
		if (searched == 0){
			cout<<"New"<<endl;
			_bottomConnexions->insert(newConnexion);
		} else {
			cout<<"Refresh"<<endl;
			searched->newConnexionRegister();
			cout<<"Ref-ser"<<endl;
			if (_bottomMinor == 0 || (_bottomMinor != searched && _bottomMinor->getWeight() >= searched->getWeight())){
				_bottomMinor = searched;
			}
			cout<<"out Ref"<<endl;
			delete newConnexion;
			cout<<"deleted"<<endl;
		}
	}
}

void AdjacencyNode::NCRAuxLeft(int pID, int pPosition){
	ConnexionNode* newConnexion = new ConnexionNode(pID);
	if (_leftConnexions == 0){
		_leftConnexions = new AVLTree<ConnexionNode>();
		_leftConnexions->insert(newConnexion);
	} else {
		ConnexionNode* searched = _leftConnexions->search(newConnexion);
		if (searched == 0){
			_leftConnexions->insert(newConnexion);
		} else {
			searched->newConnexionRegister();
			if (_leftMinor == 0 || (_leftMinor != searched && _leftMinor->getWeight() >= searched->getWeight())){
				_leftMinor = searched;
			}
			delete newConnexion;
		}
	}
}

void AdjacencyNode::NCRAuxRight(int pID, int pPosition){
	ConnexionNode* newConnexion = new ConnexionNode(pID);
	if (_rightConnexions == 0){
		_rightConnexions = new AVLTree<ConnexionNode>();
		_rightConnexions->insert(newConnexion);
	} else {
		ConnexionNode* searched = _rightConnexions->search(newConnexion);
		if (searched == 0){
			_rightConnexions->insert(newConnexion);
		} else {
			searched->newConnexionRegister();
			if (_rightMinor == 0 || (_rightMinor != searched && _rightMinor->getWeight() >= searched->getWeight())){
				_rightMinor = searched;
			}
			delete newConnexion;
		}
	}
}

void AdjacencyNode::newConnexionRegister(int pID, int pPosition){
	if (pPosition == ABOVE_POSITION){
		NCRAuxAbove(pID, pPosition);

	} else if (pPosition == BOTTOM_POSITION){
		NCRAuxBottom(pID, pPosition);		

	} else if (pPosition == LEFT_POSITION){
		NCRAuxLeft(pID, pPosition);

	} else if (pPosition == RIGHT_POSITION){
		NCRAuxRight(pID, pPosition);

	}
}

int AdjacencyNode::getBestConnexionID(int pPosition){
	if (pPosition == ABOVE_POSITION){
		return _aboveMinor->getConnexionID();
	} else if (pPosition == BOTTOM_POSITION){
		return _bottomMinor->getConnexionID();
	} else if (pPosition == LEFT_POSITION){
		return _leftMinor->getConnexionID();
	} else if (pPosition == RIGHT_POSITION){
		return _rightMinor->getConnexionID();
	} else {
		return -1;
	}
}
