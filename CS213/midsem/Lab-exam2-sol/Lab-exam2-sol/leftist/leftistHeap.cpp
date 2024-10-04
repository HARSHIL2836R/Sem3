#include "leftistHeap.h"

// Initialize an instance of LeftistNode
LeftistNode::LeftistNode(int key, LeftistNode *lt, LeftistNode *rt, int np)
{
    this->key = key;
    right = rt;
    left = lt,
    npl = np;
}

// Implement a default constructor for a empty LeftistHeap
LeftistHeap::LeftistHeap()
{
    root = nullptr;
}

// Implement a destructor for LeftistHeap
// All nodes should be properly deleted to avoid memory leaks
LeftistHeap::~LeftistHeap()
{
    makeEmpty();
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
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;
    if (h1->key < h2->key)
    {
        if (h1->left == NULL)
            h1->left = h2;
        else
        {
            h1->right = merge(h1->right, h2);
            if (h1->left->npl < h1->right->npl)
                swapChildren(h1);
            h1->npl = h1->right->npl + 1;
        }
        return h1;
    }
    else
    {
        if (h2->left == NULL)
            h2->left = h1;
        else
        {
            h2->right = merge(h2->right, h1);
            if (h2->left->npl < h2->right->npl)
                swapChildren(h2);
            h2->npl = h2->right->npl + 1;
        }
        return h2;
    }
}

// Implement a function to swap the children of a node (Exchange the left and right children of the provided node)
// Ensure the left child becomes the right child and vice versa.
void LeftistHeap::swapChildren(LeftistNode *t)
{
    LeftistNode *tmp = t->left;
    t->left = t->right;
    t->right = tmp;
}

// Implement a insertion function to insert a new key into the heap.
void LeftistHeap::insert(int &x)
{
    root = merge(new LeftistNode(x), root);
}

// Implement this function to retrieve the smallest key in the heap.
int LeftistHeap::findMin() const
{
    if (isEmpty())
        throw std::underflow_error("Heap is empty");
    return root->key;
}

// Delete minimum function: Remove and return the smallest key from the heap.
void LeftistHeap::deleteMin(int &minItem)
{
    if (isEmpty())
    {
        cout << "Heap is Empty" << endl;
        return;
    }
    minItem = findMin();
    LeftistNode *oldRoot = root;
    root = merge(root->left, root->right);
    delete oldRoot;
}

// Check if the heap is empty
bool LeftistHeap::isEmpty() const
{
    return root == nullptr;
}

void LeftistHeap::makeEmpty()
{
    makeEmpty(root);
}

// Implement a helper function for makeEmpty that delete all nodes starting from the given node.
void LeftistHeap::makeEmpty(LeftistNode *t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
}
