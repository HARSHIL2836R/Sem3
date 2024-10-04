#include "bst.h"

//
// You may use the following function to view the BST
//
//void printBST(Node* root);

int rec_findKthSmallest(Node* root, int& k) {
    if (!root) return -1;  // Base case: if root is null, return -1

    // First, try to find in the left subtree (for smaller values)
    int left = rec_findKthSmallest(root->left, k);
    if (k == 0) return left;  // If the kth smallest is already found in the left subtree, return it

    // Decrement k for the current node
    k--;
    if (k == 0) return root->data;  // If k becomes 0 at the current node, return the node's value

    // If not found, search in the right subtree
    return rec_findKthSmallest(root->right, k);
}

int findKthSmallest(Node* root, int k) {
  return rec_findKthSmallest(root, k);
}

int rec_findKthLargest(Node* root, int& k) {
    if (!root) return -1;  // Base case, if root is null

    // Traverse right subtree first (larger values)
    int right = rec_findKthLargest(root->right, k);
    if (k == 0) return right;

    k--;  // Decrement k for current node
    if (k == 0) return root->data;

    // Traverse left subtree
    return rec_findKthLargest(root->left, k);
}

int findKthLargest(Node* root, int k) {
  return rec_findKthLargest(root, k);
}
