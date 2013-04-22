/*

Author: Joseph Loaiza

*/

#ifndef CONNEXION_NODE
#define CONNEXION_NODE

#include <iostream>
using namespace std;

class ConnexionNode{
private:
	int _weight;
	int _connexionID;
public:

	bool operator==(const ConnexionNode& pToCompare){
		return _connexionID == pToCompare.getConnexionID();
	}
	bool operator<(const ConnexionNode& pToCompare){
		return _connexionID < pToCompare.getConnexionID();
	}
	bool operator>(const ConnexionNode& pToCompare){
		return _connexionID > pToCompare.getConnexionID();
	}
	bool operator<=(const ConnexionNode& pToCompare){
		return _connexionID <= pToCompare.getConnexionID();
	}
	bool operator>=(const ConnexionNode& pToCompare){
		return _connexionID >= pToCompare.getConnexionID();
	}
	bool operator!=(const ConnexionNode& pToCompare){
		return _connexionID != pToCompare.getConnexionID();
	}

	ConnexionNode(int pID){
		_weight = 200;
		_connexionID = pID;
	}
	int getWeight() const{
		return _weight;
	}

	int getConnexionID() const{
		return _connexionID;
	}

	void setWeight(int pWeight){
		_weight = pWeight;
	}

	void setConnexionID(int pID){
		_connexionID = pID;
	}

	void newConnexionRegister(){
		_weight -= 5;
	}
};



#endif /*CONEXION_NODE*/