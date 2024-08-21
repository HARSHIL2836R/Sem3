// Problem 2

// Do not include any other file
#include "bst.h"

int height(TreeNode* n) {
int h_left = 0;
int h_right = 0;
  if( n == NULL ) {
    return -1;
  }

  if((n-> left == NULL) && (n->right == NULL)) {
    return 0;
  }

  if(n->left != NULL) {
    h_left = height(n->left);
  } else {
    h_left = 0;
  }

  if(n->right != NULL) {
    h_right = height(n->right);
  } else {
    h_right = 0;
  }

  if(h_left > h_right) {
    return h_left + 1;
  } else {
    return h_right + 1;
  }
}


bool BST::rotate(int y_key) {
  if( y_key < 0) {
    return false;
  }

  if(root==NULL)return false;
    TreeNode* curr = root;
    while(true){
        if( curr->key==y_key ) {
          break;
        } else if(curr->key > y_key) {
            if(curr->left==NULL){
                return false;
            }else{
                curr = curr->left;
            }
        }else{
            if(curr->right==NULL){
                return false;
            }else{
                curr = curr->right;
            }
        }
    }

    TreeNode* par = curr -> parent;
    if(par == NULL) {
      return false;
    }

    if((par->left)->key == y_key) {
      if(height(par->right) < height(curr)){
        return false;
      }
    } else {
      if(height(par->left) < height(curr)){
        return false;
      }
    }

    TreeNode* par_par = par -> parent;
    if(par_par == NULL) {
      if(par->right->key == y_key) {
        root = curr;
        par->right = curr->left;
        curr->left = par;

        return true;
      } else {
        root = curr;
        par->left = curr->right;
        curr->right = par;

        return true;
      }
      
    } else {
      if(par_par->key < par->key) {
        if(par->right->key == y_key) {
          par_par->right = curr;
          par->right = curr->left;
          curr->left = par;

          return true;
        } else {
          par_par->right = curr;
          par->left = curr->right;
          curr->right = par;

          return true;
        }
      } else {
          if(par->right->key == y_key) {
            par_par->left = curr;
            par->right = curr->left;
            curr->left = par;

            return true;
          } else {
            par_par->left = curr;
            par->left = curr->right;
            curr->right = par;

            return true;
          }
      }
    }

  return false;
}
