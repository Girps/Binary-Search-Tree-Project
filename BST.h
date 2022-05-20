#include <iostream>

template<typename T>
class BST 
{
	private:
		/* Nested struct class, nodes refer to two child nodes and hold key and data*/
		struct Node
		{
			explicit Node(T data_Pram, int key_Pram) :data{ data_Pram }, key{ key_Pram }, right_Child{ nullptr }, left_Child{ nullptr }{}
			~Node() { std::cout << "~[ " << data << " ]";  }
			T data;
			int key;
			Node* right_Child;
			Node* left_Child;
		}; 
		// Private data fields and function memebers
	Node* root; 
	/* Node* returning function allocates node on heap and initalizes data fields */
	Node* created_Node(const T &data_Param, int key_Param) { return new Node(data_Param,key_Param);  }

	/* void recurisve function, binary inserts nodes on the tree through recursion*/
	void add_Node_Helper(Node* &root_Pram,const T &data_Pram, int key_Pram) 
	{
		// If BST is empty root gets a node, or if left or right child is nullptr they get node
		if (root_Pram == nullptr) 
		{
			root_Pram = created_Node(data_Pram,key_Pram); 
		} // If node key > key_Param recursive call left child
		else if (root_Pram->key > key_Pram) 
		{
			add_Node_Helper(root_Pram->left_Child,data_Pram,key_Pram);
		}
		else // node key < key_Param recrusive call right child 
		{
			add_Node_Helper(root_Pram->right_Child,data_Pram,key_Pram);
		}
	}

	/* T returning recrusive function removes and returns data of the node*/
	T remove_Node_Helper(Node* &root_Param,int key_Param) 
	{
		
	}

	/* Void recursive function helper postOrder traverses a BST and deletes each node*/
	void free_Node_Helper(Node* &root_Param) 
	{
		// Check left child first
		if (root_Param->left_Child != nullptr) 
		{
			free_Node_Helper(root_Param->left_Child);
		}// Check right child
		if (root_Param->right_Child != nullptr)
		{
			free_Node_Helper(root_Param->right_Child); 
		}
		// Now delete the root 
		delete root_Param; 
		// Set to null
		root_Param = nullptr; 
	}

	public: 
		BST() :root{nullptr} {}
		~BST() { free_Nodes();  std::cout << "BST freed\n";  }

		/* Void function calls recursive helper add_Node_Helper binary inserts a node */
		void add_Node(const T &data_Param, int key_Param) 
		{
			add_Node_Helper(this->root,data_Param,key_Param); 
		}

		/* T data returning function binary searches a node in bst and removes it */
		T remove_Node(int key_Param)
		{
			
		}
	
		/**/
		void po_Traverse()
		{
			
		}

		bool binary_Search(T key)
		{
			
		}

		T retrieve_Node() {} 
		/*Void function perform indirect recursion deleteing node in postOrder and deleteing root last */
		void free_Nodes() 
		{
			// Call recursive helper function
			free_Node_Helper(this->root);
			//this->root = nullptr; 
		}
};