#include "leftistHeap.h"

// Initialize an instance of LeftistNode
LeftistNode::LeftistNode(int key, LeftistNode *lt, LeftistNode *rt, int np)
{
    // Write your code below this line ----------------------------------------------------------------
    this->key = key;
    this->left = lt;
    this->right = rt;
    this->npl = np;
}
LeftistNode::~LeftistNode()=default;

// Implement a default constructor for a empty LeftistHeap
LeftistHeap::LeftistHeap()
{
    // Write your code below this line ----------------------------------------------------------------
    this->root = nullptr;
}

/* void inorder(LeftistNode* root){
    if (root == nullptr) return;
    inorder(root->left);
    inorder(root->right);
    delete root;
} */
// Implement a destructor for LeftistHeap
// All nodes should be properly deleted to avoid memory leaks
LeftistHeap::~LeftistHeap()
{
    // Write your code below this line ----------------------------------------------------------------
}

void LeftistHeap::merge(LeftistHeap &rhs)
{
    if (this == &rhs)
        return;
    root = merge(root, rhs.root);
    rhs.root = nullptr;
}

// Implement the merge function that takes roots of two LeftistHeaps and merges them into one returns the root of merged heap
LeftistNode *LeftistHeap::merge(LeftistNode *h1, LeftistNode *h2)
{
    // Write your code below this line ----------------------------------------------------------------
    LeftistNode* a;
    LeftistNode* b;
    if (h1 == nullptr) return h2;
    if (h2 == nullptr) return h1;
    if (h1 == h2) return h1;
    if (h1->key < h2->key) { a = h1; b = h2;}
    else { a = h2; b= h1;}

    LeftistNode* R1 = a->right;
    a->right = merge(R1, b);
    if (a->left == nullptr && a->right != nullptr){
        swapChildren(a);
        a->npl = 0;
    }
    else if (a->left == nullptr && a->right == nullptr){
        a->npl = 0;
    }
    else if (a->left != nullptr && a->right == nullptr){
        a->npl = 0;
    }
    else{
        if (a->left->npl < a->right->npl){
            swapChildren(a);
        }
        a->npl = a->right->npl + 1;
    }
    return a;
}

// Implement a function to swap the children of a node (Exchange the left and right children of the provided node)
// Ensure the left child becomes the right child and vice versa.
void LeftistHeap::swapChildren(LeftistNode *t)
{
    // Write your code below this line ----------------------------------------------------------------
    LeftistNode* temp = t->left;
    t->left = t->right;
    t->right = temp;
}

// Implement a insertion function to insert a new key into the heap.
void LeftistHeap::insert(int &x)
{
    // Write your code below this line ----------------------------------------------------------------
    if (root == nullptr) {
        LeftistNode new_node = LeftistNode(x);
        root = &new_node;
        return;
    }
    LeftistHeap a;
    a.insert(x);
    merge(a);
}

// Implement this function to retrieve the smallest key in the heap.
int LeftistHeap::findMin() const
{
    // Write your code below this line ----------------------------------------------------------------
    return getRoot()->key;
}

// Delete minimum function: Remove and return the smallest key from the heap.
void LeftistHeap::deleteMin(int &minItem)
{
    // Write your code below this line ----------------------------------------------------------------
    if (!root) minItem = -1;
    minItem = getRoot()->key;
    auto new_root = merge(root->left, root->right);
    delete root;
    root = new_root;
}

// Check if the heap is empty
bool LeftistHeap::isEmpty() const
{
    // Write your code below this line ----------------------------------------------------------------
  return false; //dummy return
}

void LeftistHeap::makeEmpty()
{
    makeEmpty(root);
}

// Implement a helper function for makeEmpty that delete all nodes starting from the given node.
void LeftistHeap::makeEmpty(LeftistNode *t)
{
    // Write your code below this line ----------------------------------------------------------------
}
