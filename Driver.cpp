#include<iostream>
#include "BST.h"
#include <string>

int main() 
{
	BST<std::string> tree; 
	tree.add_Node("A",1);
	tree.in_Order_Traversal(); 
	tree.remove_Node(1); 
	printf("\n");
	return 0; 
}