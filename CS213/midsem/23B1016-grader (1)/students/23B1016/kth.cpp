#include "bst.h"

//
// You may use the following function to view the BST
//
//void printBST(Node* root);

Node* prev_root = nullptr;
int* arr = new int[1]{'\0'};
int sz = 0;
int cap = 1;

void inorder(Node* node, int* &arr, int& sz, int& cap){
  if (node == nullptr){
    return;
  }
  inorder(node->left, arr, sz, cap);
  if (cap < ++sz){
    cap = 2*cap;
    int *new_arr = new int[cap];
    for (int i = 0; i < cap/2; i++)
    {
      new_arr[i] = arr[i];
    }
    arr = new_arr;
  }
  arr[sz-1] = node->data;
  inorder(node->right,arr,sz, cap);
}

/*int findKthSmallest(Node* root, int k) {
  if (arr[0] == '\0' && prev_root == nullptr) 
    inorder(root, arr);
  else if (prev_root != root)    
    inorder(root, arr);
  prev_root = root;
  if (k > sz || k <= 0) return -1;
  int a = arr[k-2];
  return arr[k-1];
}*/
int findKthSmallest(Node* root, int k) {
  int* arr = new int[1]{'\0'};
  int sz = 0;
  int cap = 1;
  inorder(root,arr,sz,cap);
  if (k > sz || k <= 0) return -1;
  return arr[k-1];
}


/*int findKthLargest(Node* root, int k) {
  if (arr[0] == '\0' && prev_root == nullptr) inorder(root, arr);
  else if (prev_root != root) inorder(root, arr);
  prev_root = root;
  if (k > sz || k <= 0) return -1;
  return arr[sz - k];
}*/
int findKthLargest(Node* root, int k) {
  int* arr = new int[1]{'\0'};
  int sz = 0;
  int cap = 1;
  inorder(root,arr,sz,cap);
  if (k > sz || k <= 0) return -1;
  return arr[sz - k];
}

