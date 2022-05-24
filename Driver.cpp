#include<iostream>
#include "BST.h"
#include <string>

int main() 
{
	BST<std::string> tree; 
	tree.add_Node("A",10);
	tree.add_Node("B",5);
	tree.add_Node("C", 12); 
	tree.in_Order_Traversal(); 
	tree.remove_Node(10); 
	printf("\n");
	tree.in_Order_Traversal(); 
	return 0; 
}