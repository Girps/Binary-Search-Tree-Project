#include<iostream>
#include "BST.h"
#include <string>

int main() 
{
	BST<int> tree; 

	tree.add_Node(1,1);
	tree.add_Node(2,2);
	tree.add_Node(3,3); 

	BST<int> tree2 = tree;
	tree2.pre_Order_Traveral(); 

	return 0; 
}