#include <iostream>

struct no_Such_Element_Execption{};


template<typename T>
class BST 
{
	private:
		/* Nested struct class, nodes refer to two child nodes and hold key and data*/
		struct Node
		{	
			T data;
			int key;
			Node* right_Child;
			Node* left_Child;
			explicit Node(T data_Pram, int key_Pram) :data{ data_Pram }, key{ key_Pram }, right_Child{ nullptr }, left_Child{ nullptr }{}
			~Node() { std::cout << "~( " << this->data << " , " << "key: " << this->key << " )"; }
			
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

	/* Void recursive function, traverses BST from root, left subtree to right subtree, passes by pointer
		reference with const data */
	void pre_Order_Traversal_Helper( Node* const &root_Param) 
	{
		// Print node 
		std::cout << "( " << root_Param->data << " , key: " << root_Param->key << " )"; 
		// Traverse left subtree
		if (root_Param->left_Child != nullptr)
		{
			pre_Order_Traversal_Helper(root_Param->left_Child);
		}
		// Traverse right subtree 
		if (root_Param->right_Child != nullptr)
		{
			pre_Order_Traversal_Helper(root_Param->right_Child);
		}
	}

	/* Void */
	void post_Order_Traversal_Helper(Node* const& root_Param) 
	{
		// Traverse left subtree
		if (root_Param->left_Child != nullptr) 
		{
			post_Order_Traversal_Helper(root_Param->left_Child);
			std::cout << "( " << root_Param->left_Child->data << " , key: " <<
				root_Param->left_Child->key << " )"; 
		}
		if (root_Param->right_Child != nullptr)
		{
			post_Order_Traversal_Helper(root_Param->right_Child); 
			std::cout << "( " << root_Param->right_Child->data << " , key: " <<
				root_Param->right_Child->key << " )";
		}
	}

	/*Void recursive helper function postOrder traverse and prints nodes*/
	void in_Order_Traversal_Helper(Node* const& root_Param)
	{
		// Traverse in left subtree
		if (root_Param->left_Child != nullptr)
		{
			in_Order_Traversal_Helper(root_Param->left_Child);
		}
		// Print root data
		std::cout << "( " << root_Param->data << ", key: " << root_Param->key << " )"; 
		// Traverse in right subtree 
		if (root_Param->right_Child != nullptr)
		{
			in_Order_Traversal_Helper(root_Param->right_Child);
		}
	}

	/* T returning recursive function, binary searches a node, removes and returns its data */
	T remove_Node_Helper(Node* &root_Param,int key_Param) 
	{
		// If key not found throw an exception
		if (root_Param == nullptr) { throw no_Such_Element_Execption{}; }
		// If root found remove node and return 
		if (root_Param->key == key_Param) 
		{
			//case  1 no children
			if (root_Param->left_Child == nullptr && root_Param->right_Child == nullptr) 
			{
				// Get root data 
				T data = root_Param->data; 
				// Delete node 
				delete root_Param; 
				// Set to nullptr
				root_Param = nullptr; 
				return data; 
			} // Case 2 1 child on the left
			else if(root_Param->left_Child != nullptr && root_Param->right_Child == nullptr)
			{
				// Remove root make left child the new root return data
				Node* target = root_Param;
				root_Param = root_Param->left_Child; 
				T data = target->data; 
				delete target;
				return data; 
			} // Case 3 1 child on the right
			else if (root_Param->left_Child == nullptr && root_Param->right_Child != nullptr)
			{
				// Remove root make right child the new root return data
				Node* target = root_Param;
				root_Param = root_Param->right_Child;
				T data = target->data;
				delete target;
				return data;
			} // case 4 two children 
			else 
			{
				Node* target = root; 
				// New root is child with larger key
				if (root_Param->left_Child->key > root_Param->right_Child->key) 
				{
					root_Param = root_Param->left_Child; 
				}
				else
				{
					root_Param = root_Param->right_Child; 
				}
				T data = target->data; 
				delete target; // delete old root
				return data; 
			}
		}
		else if(key_Param > root_Param->key) // not in root recursive call
		{
			// Binary search
			remove_Node_Helper(root_Param->left_Child, key_Param);
		}
		else
		{
			remove_Node_Helper(root_Param->right_Child, key_Param);
		}
	}
	public: 
		BST() :root{nullptr} {}
		~BST() { free_Nodes();  std::cout << "\n~BST freed~\n";  }

		/* Getter function returns data of the root node*/
		T get_Root() 
		{
			return this->root->data; 
		}

		/* Getter function returns key of the root node */
		int get_Root_Key() 
		{
			this->root->key; 
		}

		/* Void function calls recursive helper add_Node_Helper binary inserts a node */
		void add_Node(const T &data_Param, int key_Param) 
		{
			add_Node_Helper(this->root,data_Param,key_Param); 
		}

		/* T data returning function binary searches a node in bst and removes it */
		T remove_Node(int key_Param)
		{
				return remove_Node_Helper(this->root,key_Param);
		}
	
		/* Void function calls recursive helper function that prints data in PreOrder*/
		void pre_Order_Traveral() { pre_Order_Traversal_Helper(this->root); };

		/* Void function calls recursive helper function prints data in PostOrder*/
		void post_Order_Traversal()
		{ 
			post_Order_Traversal_Helper(this->root);
			std::cout << "( " << root->data << " , key: " <<
			root->key << " )";
		}

		void in_Order_Traversal() 
		{
			in_Order_Traversal_Helper(this->root); 
		}

		bool binary_Search(T key)
		{
			
		}

		T retrieve_Node() {} 

		/*Void function calls recursive helper funciton deleteing node in postOrder and deleteing root last */
		void free_Nodes() 
		{
			// Call recursive helper function
			if (root != nullptr) 
			{
				free_Node_Helper(this->root);
			}
		}
};