#include <math.h>
#include <stdlib.h>
#include <iostream>
//#include "AVLTree.h"
#include "AdjacencyNode.h"
#include "AdjacencyNode.cpp"
using namespace std;

// int main(){
// 	AVLTree<int>* tree = new AVLTree<int>();
// 	int* m;
// 	for (int i = -34; i < 100; i++){
// 		int* n = new int(rand()%1000*i+i);
// 		if (i == 50){
// 			m = n;
// 		}
// 		tree->insert(n);
// 	}
// 	cout<<"here"<<endl;
// 	tree->printTree(AVLTree<int>::IN_ORDER_TRAVERSAL);
// 	cout<<"going to search: "<<*m<<endl;
// 	int* s = tree->search(m);
// 	cout<<(s!=0?*s:-1)<<endl;
// }

int main(){
	AdjacencyNode* node = new AdjacencyNode(1);
	int na[100];
	for (int i = 0; i< 100; i++){
		na[i] = 0;
	}

	int ma = 0;

	for (int i = 0; i < 1000; i++){
		int n = rand()%100;
		int p = rand()%100/100.0*4;

		if (p == 1){
			na[n] += 10;
			if (na[n] >= na[ma]){
				ma = n;
			}
		}

		cout<<"i:"<<i<<" n:"<<n<<" p:"<<p<<endl;
		node->newConnexionRegister(n, p);
	}
	cout<<"m:"<<ma<<" node:"<<node->getBestConnexionID(1)<<endl;

	return 0;
}