#include "rb.h"
using ptr = RedBlackTree::ptr;

RedBlackTree::RedBlackTree(){}

const ptr RedBlackTree::getRoot() const
{ 
	return root;
}

ptr RedBlackTree::insert(int data)
{
	ptr newnodePtr = new node(data);
	if (!root) {
		root = newnodePtr;
		root->color = 0; // set root color as black
		return newnodePtr;
	}
	insert(root, newnodePtr);
	return newnodePtr;
}

// auxiliary function to perform RBT insertion of a node
// you may assume start is not nullptr
void RedBlackTree::insert(ptr start, ptr newnodePtr)
{
	// choose direction
	if (start->data <= newnodePtr->data){
		if (start->right == nullptr){
			start->right = newnodePtr;
			newnodePtr->parent = start;
			if (newnodePtr->parent->color == 1){
				fixup(newnodePtr);
			}
			return;
		}
		insert(start->right,newnodePtr);
	}
	else if (start->data >= newnodePtr->data){
		if (start->left == nullptr){
			start->left = newnodePtr;
			newnodePtr->parent = start;
			if (newnodePtr->parent->color == 1){
				fixup(newnodePtr);
			}
			return;
		}
		insert(start->left,newnodePtr);
	}

	return;
}

// Credits to Adrian Schneider
void RedBlackTree::printRBT(ptr start, const std::string& prefix, bool isLeftChild) const
{
	if (!start) return;

	std::cout << prefix;
	std::cout << (isLeftChild ? "|--" : "|__" );
	// print the value of the node
	std::cout << start->data << "(" << start->color << ")" << std::endl;
	// enter the next tree level - left and right branch
	printRBT(start->left, prefix + (isLeftChild ? "│   " : "    "), true);
	printRBT(start->right, prefix + (isLeftChild ? "│   " : "    "), false);
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightrotate(ptr loc){ //don't care about conflicts here
	if (loc->left == nullptr){
		return;
	}

	ptr p = loc->parent;

	if (p == nullptr){
		root = loc->left;
	}

	else if (p->right != nullptr && p->right == loc){
		p->right = loc->left;
	}
	else{
		p->left = loc->left;
	}
	loc->left->parent = p;

	ptr c = loc->left->right;
	loc->left->right = loc;
	if (c == nullptr){
		loc->left = nullptr;
	}
	else {
		loc->left = c;
		c->parent = loc;
	}
}

// Function performing left rotation
// of the passed node
void RedBlackTree::leftrotate(ptr loc){
	if (loc->right == nullptr){
		return;
	}

	ptr p = loc->parent;

	if (p == nullptr){
		root = loc->right;
	}

	else if (p->right != nullptr && p->right == loc){
		p->right = loc->right;
	}
	else{
		p->left = loc->right;
	}
	loc->right->parent = p;

	ptr c = loc->right->left;
	loc->right->left = loc;
	if (c == nullptr){
		loc->right = nullptr;
	}
	else {
		loc->right = c;
		c->parent = loc;
	}
	
}

// This function fixes violations
// caused by RBT insertion
void RedBlackTree::fixup(ptr loc) //Conflict between current node and parent node
{//parent is red => parent is not root
	if (loc->parent == nullptr){
		loc->color = 0;
		return;
	}
	if (!(loc->color == 1 && loc->parent->color == 1)){
		return;
	}
	ptr uncle = loc->parent->data > loc->parent->parent->data ? loc->parent->parent->left : loc->parent->parent->right;

	if (uncle == nullptr || uncle->color == 0){
		bool straight = loc->data > loc->parent->data ? (loc->parent->data > loc->parent->parent->data ? true : false): (loc->parent->data > loc->parent->parent->data ? false : true);
		if (!straight){
			bool right = (loc->data > loc->parent->data) ? false : true;
			if (right) rightrotate(loc->parent);
			else leftrotate(loc->parent);
			fixup(loc);
		}
		else{
			loc->parent->color = 0;
			loc->parent->parent->color = 1;
			bool left = (loc->data > loc->parent->data) ? true:false;
			if (left){
				leftrotate(loc->parent->parent);
			}
			else {
				rightrotate(loc->parent->parent);
			}
		}
	}
	else if (uncle->color == 1){
		uncle->color = 0;
		loc->parent->color = 0;
		loc->parent->parent->color = 1;
		fixup(loc->parent->parent);
	}
}

// Function to print inorder traversal
// of the fixated tree
void RedBlackTree::inorder(ptr start) const
{
	if (!start)
		return;
	
	inorder(start->left);
	std::cout << start->data << " ";
	inorder(start->right);
}

// driver code
int main()
{
	int n; std :: cin >> n;
	assert (n < 10000 && n >= 0);
	int a[10000];
	RedBlackTree tree;

	for (int i = 0; i < n; i++) {
		std::cin >> a[i];

		// allocating memory to the node and initializing:
		// 1. color as red
		// 2. parent, left and right pointers as NULL
		// 3. data as i-th value in the array

		// calling function that performs rbt insertion of
		// this newly created node
		auto newnodePtr = tree.insert(a[i]);

		// calling function to preserve properties of rb
		// tree
		tree.fixup(newnodePtr);
	}
	tree.printRBT(tree.getRoot());

	return 0;
}
