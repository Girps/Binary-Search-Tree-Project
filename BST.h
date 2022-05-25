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

	/* Recursive void function help deep copy another tree to this
		tree instance*/
	void pre_Order_Copy(Node* const &root_Param) 
	{
		this->add_Node(root_Param->data,root_Param->key); 
		// Traverse left subtree
		if (root_Param->left_Child != nullptr)
		{
			pre_Order_Copy(root_Param->left_Child);
		}
		// Traverse right subtree 
		if (root_Param->right_Child != nullptr)
		{
			pre_Order_Copy(root_Param->right_Child);
		}
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
			} /*Case 4: Node with two children find min key of right subtree and have it become new root*/
			else 
			{
				Node* target = root; 
				// New root is min node in right subtree of root
				Node* temp = find_Min_Node(root->right_Child);
				target->data = temp->data; // Copy data
				target->key = temp->key; // Copy key
				// Now remove node from the BST
				return remove_Node_Helper(root->right_Child,temp->key);

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

	/* Pointer returnign function, returns a pointer to smallest node in the BST */
	Node* find_Min_Node(Node* root_Param)
	{
		// Recursive case if their is a left child recurive call 
		if (root_Param->left_Child != nullptr)
		{
			return find_Min_Node(root_Param->left_Child); 
		}
		else // Base case if not left child pointer carrying its address 
		{
			return root_Param; 
		}
		
	}

	/*Bool returning function, binary searches tree for a key given by the argument value*/
	bool binary_Search_Helper(Node* root_Param, int key_Param) 
	{
		// if list is node is not present return flase
		if (root_Param == nullptr) 
		{
			false; 
		}
		// if root->key == key_Param return true
		if (root_Param->data == key_Param) 
		{
			return true; 
		}
		// if key is larger traverse to right sub tree
		if (key_Param > root_Param->key) 
		{
			binary_Search_Helper(root_Param->right_Child); 
		}
		// if key is smaller traverse to left subtree 
		else
		{
			binary_Search_Helper(root_Param->right_Child);
		}
	}

	/* T returning recurisve function binar searches node with matching key and 
		returns by values its data */
	T retrieve_Node_Helper(Node* root_Param, int key_Param) 
	{
		/*If not found return an exception */
		if (root_Param)
		{
			throw no_Such_Element_Execption{}; 
		}

		// if root->key == key_Param return true
		if (root_Param->data == key_Param)
		{
			return root_Param->data; 
		}
		// if key is larger traverse to right sub tree
		if (key_Param > root_Param->key)
		{
			retrieve_Node_Helper(root_Param->right_Child);
		}
		// if key is smaller traverse to left subtree 
		else
		{
			retrieve_Node_Helper(root_Param->right_Child);
		}
	}

	public: 
		BST() :root{nullptr} {}
		~BST() { free_Nodes();  std::cout << "\n~BST freed~\n";  }

		/* Move constructor takes resources of rr value of type BST*/
		BST(BST&& rr_BST) 
		{
			// Assign this instance's root pointer to rr value root 
			this->root = rr_BST.root; 
			// Now set the other root to null pointer
			rr_BST.root = nullptr; 
		}

		/* Deep copy constructor PreOrder copies parameter BST */ 
		BST(const BST& rr_BST ) 
		{
			std::cout << "Deep copy constructor called";
			this->pre_Order_Copy(rr_BST.root); 
		}

		/* Overloaded assignment operator deep copies BST in paramter to 
			this instance, return a refence to support chaining */
		BST& operator = (const BST& rr_BST) 
		{
			// Avoid self assignment
			if (&rr_BST == this)
			{
				return *this; 
			}
			else 
			{
				// Free node
				free_Nodes(); 
				this->pre_Order_Copy(rr_BST.root);
			}
		}

		/* Move assignment operator overloaded, returns a referecence to support chaining*/
		BST& operator = (BST&& rr_BST) 
		{
			// Avoid self assignment
			if(&rr_BST == this)
			{
				return *this; 
			}
			else 
			{
				// Otherwise free nodes and take resources of rr BST
				this->free_Nodes(); 
				this->root = rr_BST.root; 
				rr_BST.root = nullptr; 
			}
		}

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

		/* Void function calls recurisve helper and prints data inOrder*/
		void in_Order_Traversal() 
		{
			in_Order_Traversal_Helper(this->root); 
		}

		/* Bool retuning function member calls a recurivse function that binary search a node with matching key*/
		bool binary_Search(T key,int key_Param)
		{
			return binary_Search_Helper(this->root, key_Param); 
		}

		/* Function memeber returns by value data from BST with matching key*/
		T retrieve_Node(int key_Param)
		{
			return retrieve_Node_Helper(this->root, key_Param);

		} 

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