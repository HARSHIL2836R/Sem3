// Problem 1

#include "bst.h"

bool func(TreeNode *n) {
  if(n == NULL) {
    return true;
  }

  if( n->left != NULL) {
    if( n-> key < (n->left)->key) {
      return false;
    }
  }

  if( n-> right != NULL) {
    if( n->key > (n->right)->key) {
      return false;
    }
  }

  if ((n->left == NULL)&&(n->right == NULL)) {
    return true;
  } else {
    if(n->left != NULL) {
      if(func(n->left) == false) {
        return false;
      }
    }

    if(n->right != NULL) {
      if(func(n->right) == false) {
        return false;
      }
    }
  }

  return true; 
}

bool BST::isBST() {
  return func(root);
}
