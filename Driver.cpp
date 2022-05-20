#include<iostream>
#include "BST.h"
#include <string>

int main() 
{
	BST<std::string> tree; 
	tree.add_Node("Jesse", 10);
	tree.add_Node("Bob",5);
	tree.add_Node("Cheg", 20);
	tree.add_Node("Alpha",25);
	return 0; 
}