#ifndef BST__H
#define BST__H

#include "node.h"
#include <queue>
#include <list>
#include <stack>
#include <vector>

// recursively to visit all the node
template<typename T>
void DFS_visitNode(Node<T>*);

template<typename T>
std::ostream& operator<<(std::ostream&, const Node<T>*);

template <typename T>
class BST{
public:
	int size;
	int capacity;
	int branch;// how many branches are there for this tree
	Node<T>* root;
	std::vector<Node<T>*> sonNode;

	BST();
	~BST();

	void insertNode(const T);
	Node<T>* findNode(T);
	Node<T>* findNode(T,Node<T>*);

	bool deleteNode(T);
	void mergeTree(Node<T>*, Node<T>*);//not implemented yet
	void clear();
	void inorderTraversal(Node<T>*);
	Node<T>* findMin(Node<T>*);// input is the starting root node
	Node<T>* findMax(Node<T>*);// input is the starting root node
	Node<T>* predecessor(T);
	Node<T>* successor(T);
	int getHeight(Node<T>*);//get the height of the tree recursively, from the current to the left node
	int getDistance(Node<T>*);//get the distance between the current node and root
	void DFS(Node<T>*);// depth first search
	void BFS(Node<T>*);// breath first search
	bool isBlanced(Node<T>*);//whether this tree is blanced or not
	void createBinaryTreeWithArray(T*, int);
	Node<T>* makeBSTwithSorttedArray(T*, int, int);
	std::list<Node<T>*> getRoute(Node<T>* node);//get a list of Route for a given node
	void printTree();
};
//------ get a list of route for a given node ------
// not recursive way to achieve it
template<typename T>
std::list<Node<T>* > BST<T>::getRoute(Node<T>* node){
	std::list<Node<T>*> rlist;
	Node<T>* cNode = root;
	while(1){
		Node<T>* tmpNode = cNode;
		rlist.push_back(tmpNode);
		if(cNode->member == node->member)
			break;
		else{
			if(cNode->member > cNode->member){
				if(cNode->left != nullptr)
					cNode = cNode->left;
				else{
					std::cout<<"cannot find this node"<<std::endl;
					break;
				}
			}
			else
				if(cNode->right != nullptr)
					cNode = cNode->right;
				else{
					std::cout<<"cannot find this node"<<std::endl;
					break;
				}
		}
	}
	return rlist;
}

// still something wrong with it
//------ whether this tree is blanced or not ------
// normally, this node should be the root
// achieve this function using recursive method
template<typename T>
bool BST<T>::isBlanced(Node<T>* node){
// recursively get the blanced information
// only check whether the height betwween max and min is less than 2
/*
	if(node->left==nullptr && node->right==nullptr){
		return true;
	}
	if(isBlanced(node->left) && isBlanced(node->right)){
		return true;
	}
*/
// search + getHeight method the time is O(n2)
// key information is the check left and right subtree's height
	if(node == nullptr)
		return true;
	if(abs( getHeight(node->left) - getHeight(node->right)) <=1){
		if(isBlanced(node->left) && isBlanced(node->right))
				return true;
	}
	else{
		return false;
	}
}

// BFS function written in non-recursive way
template<typename T>
void BST<T>::BFS(Node<T>* start){
	std::queue<Node<T>* > q;
	Node<T>* tmpNode = nullptr;
	q.push(start);
	while(!q.empty()){
		tmpNode = q.front();
		q.pop();
		std::cout<<tmpNode->member<<std::endl;
		if(tmpNode->left != nullptr) q.push(tmpNode->left);
		if(tmpNode->right!= nullptr) q.push(tmpNode->right);
	}
}




// include two ways to achieve DFS function
// below is the recursive way
template<typename T>
void BST<T>::DFS(Node<T>* start){
	inorderTraversal(root);
	DFS_visitNode(start);
}

//this function is just a traversal function
//it can add some specific function to achieve different goal
template<typename T>
void DFS_visitNode(Node<T>* node){
	//----- search all the left node ------
	/*
	if(node->left == nullptr && node->right == nullptr){
		std::cout<<node->member<<std::endl;
		return;
	}
	*/
	//else{
		node->status = grey;
		if(node->left != nullptr)
			DFS_visitNode(node->left);
		if(node->right!= nullptr)
			DFS_visitNode(node->right);
		node->status = black;
		std::cout<<node->member<<std::endl;
		return;
	//}
}

//overload << operator
template<typename T>
std::ostream& operator<<(std::ostream& out, const Node<T>* node){
	if(node == nullptr)
		return out<<"null"<<'\n';
	else
		return	out<<node->member<<'\n';
}

//get the height of the tree recursively
template<typename T>
int BST<T>::getHeight(Node<T>* node){
	if(node != nullptr){
		int l = getHeight(node->left);
		int r = getHeight(node->right);
		return (l>r?l:r)+1;
	}
	else{
		return 0;
	}
}

//------ get the distance between the current node and root ------
template<typename T>
int BST<T>::getDistance(Node<T>* node){
	//this function can be achieved by getHeight
}

//------ bst construction function ------
template<typename T>
BST<T>::BST():
	size(0),
	capacity(10),
	branch(2),//default is a binary tree
	root(nullptr),
	sonNode()
{
	std::cout<<"default construct BST"<<std::endl;
}

template<typename T>
BST<T>::~BST(){
	clear();
	std::cout<<"distruct BST"<<std::endl;
}



//------ inorder traversal all the nodes in the list ------
// written in recursive method
template<typename T>
void BST<T>::inorderTraversal(Node<T>* node){
	if(node == nullptr){
//		std::cout<<"inorderTraversl: list is empty"<<std::endl;
		return;
	}
	else{
		inorderTraversal(node->left);
		std::cout<<node->member<<std::endl;
		node->status = white;
		inorderTraversal(node->right);
	}
}

//------ find the min of the bst ------
template<typename T>
Node<T>* BST<T>::findMin(Node<T>* node){
	Node<T>* tmpPtr = node;
	while(tmpPtr->left != nullptr){
		tmpPtr = tmpPtr->left;
	}
	return tmpPtr;

}



//------ find the max of the bst ------
template<typename T>
Node<T>* BST<T>::findMax(Node<T>* node){
	Node<T>* tmpPtr = node;
	while(tmpPtr->right != nullptr){
		tmpPtr = tmpPtr->right;
	}
	return tmpPtr;
}

//------ insert a new node into the structure ------
template<typename T>
void BST<T>::insertNode(const T val){
	Node<T>* newNode = new Node<T>(val);

	if(size == 0)
		root = newNode;
	else{
		Node<T>* tmpPtr = root;
		while(1){
			if(newNode->member > tmpPtr->member){
				if(tmpPtr->right == nullptr){
					tmpPtr->right = newNode;
					newNode->parent = tmpPtr;
					break;
				}
				else
					tmpPtr = tmpPtr->right;
			}
			else{
				if(tmpPtr->left == nullptr){
					tmpPtr->left = newNode;
					newNode->parent = tmpPtr;
					break;
				}
				else{
					tmpPtr = tmpPtr->left;
				}
			}
		}
	}
	size++;
}

//------ given a array anad make a binary tree ------
template<typename T>
void BST<T>::createBinaryTreeWithArray(T* inputArray,int size){
	int count = 0;
	Node<T>* cNode = new Node<T>(inputArray[0]);
	root = cNode;
	std::queue< Node<T>* > q;
	q.push(cNode);
	for(int i=1;i<size;i++){
		Node<T>* z = new Node<T>(inputArray[i]);
		if(cNode->member == 0 ){// or equal to nullptr
			cNode = z;
			q.pop();
			continue;
		}
		else{
			if(count == 2){
				cNode = q.front();
				q.pop();
				count = 0;
				cNode = z;
			}
			else{
				// suppose each node c has member variable named sonNode which is a pointer
				q.push(cNode->sonNode[count]);
				cNode->sonNode[count] = z;
				count++;
			}
		}
	}
}

//------ given a sorted array and make a binary search tree ----
// this function is a spcification for the upper function
// it is a recursive method
template<typename T>
Node<T>* BST<T>::makeBSTwithSorttedArray(T* array,int start,int end){
	int mid = (end - start)/2 + start;
	if(end - start <= 1) return nullptr;
	T value = array[mid];
	Node<T>* z = new Node<T>(value);
	if(mid ==0) return z;
	else{
			z->left = makeBSTwithSorttedArray(array,start,mid);
			z->right = makeBSTwithSorttedArray(array,mid,end);
	}
}

/* delete node using order number
order: should begin from 0, keep same setting in main file
*/
template<typename T>
bool BST<T>::deleteNode(T value){
	if(size == 0){
		std::cout<<"bst is empty"<<std::endl;
		return false;
	}
	Node<T>* node = findNode(value);
	if(node == nullptr){
		std::cout<<"this value does not exist"<<std::endl;
		return false;
	}
	//case I: node has no child
	if(node->left == nullptr && node->right == nullptr){
		if(node->member < node->parent->member)
			node->parent->left = nullptr;
		else
			node->parent->right= nullptr;
		delete node;
		size--;
		return true;
	}
	//case II: node has one child
	if(node->left == nullptr xor node->right == nullptr){
		if(node->member > node->parent->member){
			if(node->right != nullptr)
				node->parent->right = node->right;
			else
				node->parent->right = node->left;
		}
		else{
			if(node->right != nullptr){
				node->parent->left= node->right;
				node->right->parent = node->parent;
			}
			else{
				node->parent->left = node->left;
				node->left->parent = node->parent;
			}
		}
		delete node;
		size--;
		return true;
	}
	//case III: node has two children
	if(node->left != nullptr && node->right != nullptr){
		Node<T>* tmp = successor(node->member);
		Node<T>* suc= new Node<T>(tmp->member);
		deleteNode(tmp->member);

		if(node->left != nullptr){
			node->left->parent = suc;
			suc->left = node->left;

		}

		if(node->right!= nullptr){
			node->right->parent = suc;
			suc->right = node->right;
		}

		suc->parent = node->parent;
		if(node == root) root = suc;

		delete node;
		size--;
		return true;
	}
}


//------ search a node in iteration way ------
template<typename T>
Node<T>* BST<T>::findNode(T value){
	if(size == 0){
		std::cout<<"findNode: list is empty"<<std::endl;
		return nullptr;
	}
	Node<T>* tmpPtr = root;
	int i;
	while(1){
		if(tmpPtr->member == value)
			return tmpPtr;
		if(tmpPtr->member > value){
			tmpPtr = tmpPtr->left;
		}
		else{
			tmpPtr = tmpPtr->right;
		}
		i++;
		if(i==size){
			std::cout<<"list do not have this value"<<std::endl;
			return nullptr;
		}
	}
}

// ------ search a node in recursive way ------
template<typename T>
Node<T>* BST<T>::findNode(T value, Node<T>* node){
	Node<T>* tmpPtr;
	if(node->member == value)
		return node;
	if(node->left ==  nullptr && node->right == nullptr)
		return nullptr;
	if(node-> member > value){
	  	tmpPtr = findNode(value,node->left);
	}
	else{
		tmpPtr = findNode(value,node->right);
	}
	return tmpPtr;
}

// ------ clear all the contents in the list ----
template<typename T>
void BST<T>::clear(){
	if(size != 0){
	Node<T>* tmpPtr = root;
	Node<T>* deletePtr;

	for(int i=0;i<size;i++){
		deletePtr = tmpPtr;
		tmpPtr = tmpPtr -> next;
		delete deletePtr;
	}
	size = 0;
	capacity = 1;
	}
}

//------ find the predecessor in ths list ------
template<typename T>
Node<T>* BST<T>::predecessor(T value){
	Node<T>* tmpPtr= findNode(value);
	if(tmpPtr->left== nullptr){
		//Node<T>* tmpPtr = node->parent;
		while(1){
			if(tmpPtr->parent->right == tmpPtr)
				return tmpPtr->parent;
			else
				tmpPtr = tmpPtr->parent;
			if(tmpPtr->parent == nullptr){
				//std::cout<<"null"<<std::endl;
				return nullptr;
				break;
			}
		}
	}
	else{
		return findMax(tmpPtr->left);
	}
}

//------ find the successor in ths list ------
template<typename T>
Node<T>* BST<T>::successor(T value){
	Node<T>* tmpPtr= findNode(value);
	if(tmpPtr->right == nullptr){
		//Node<T>* tmpPtr = node->parent;
		while(1){
			if(tmpPtr->parent->left == tmpPtr)
				return tmpPtr->parent;
			else
				tmpPtr = tmpPtr->parent;
			if(tmpPtr->parent == nullptr){
				//std::cout<<"null"<<std::endl;
				return nullptr;
				break;
			}
		}
	}
	else{
		return findMin(tmpPtr->right);
	}
}

// print this tree in a tree order
template<typename T>
void BST<T>::printTree(){
	// something like a BFS traversal
	
}
#endif
