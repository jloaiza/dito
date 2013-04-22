/*

Author: Joseph Loaiza

*/

#ifndef ADJACENCY_NODE
#define ADJACENCY_NODE

#include "AVLTree.h"
#include "ConnexionNode.h"

class AdjacencyNode{
private:
	AVLTree<ConnexionNode>* _aboveConnexions;
	AVLTree<ConnexionNode>* _bottomConnexions;
	AVLTree<ConnexionNode>* _rightConnexions;
	AVLTree<ConnexionNode>* _leftConnexions;
	ConnexionNode* _aboveMinor;
	ConnexionNode* _bottomMinor;
	ConnexionNode* _rightMinor;
	ConnexionNode* _leftMinor;
	int _figureID;

	void NCRAuxAbove(int pID, int pPosition);
	void NCRAuxBottom(int pID, int pPosition);
	void NCRAuxLeft(int pID, int pPosition);
	void NCRAuxRight(int pID, int pPosition);

public:
	static const int ABOVE_POSITION = 0;
	static const int BOTTOM_POSITION = 1;
	static const int LEFT_POSITION = 2;
	static const int RIGHT_POSITION = 3;

	AdjacencyNode(int pID){
		_figureID = pID;
		_aboveMinor = _bottomMinor = _rightMinor = _leftMinor = 0;
		_aboveConnexions = _bottomConnexions = _rightConnexions = _leftConnexions = 0;
	}

	int getFigureID() const {
		return _figureID;
	}

	void setFigureID(int pID){
		_figureID = pID;
	}

	int getBestConnexionID(int pPosition);
	void newConnexionRegister(int pID, int pPosition);
};


#endif /*ADJACENCY_NODE*/