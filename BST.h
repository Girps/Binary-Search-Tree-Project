#include <iostream>

template<typename T>
class BST 
{
	public:
		BST() {}
		~BST() {}
	private: 
		struct Node
		{
			explicit Node(T data_Pram, int key_Pram) :data{ data_Pram }, key{ key_Pram } {}
			T data;
			int key;
			Node* right_Child;
			Node* left_Child;
		}; 

	Node* root; 

	public: 

};