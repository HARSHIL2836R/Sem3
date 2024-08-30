#include "tree.h"

// Function which returns lca node of given nodes 'a' and 'b'
TreeNode* TREE::findlca(TreeNode* a, TreeNode* b) {
  
  if (a == nullptr || b == nullptr){
    return nullptr;
  }
  else if (a == b){
    return a;
  }
  else if (a->parent == b){
    return b;
  }
  else if (b->parent == a){
    return a;
  }
  else if (a->parent == b->parent){
    return a->parent;
  }
  else{
    int depth_a = 0;
    int depth_b = 0;
    TreeNode* dummy_a = a;
    TreeNode* dummy_b = b;

    while (dummy_a->parent != nullptr){
      dummy_a = dummy_a->parent;
      depth_a++;
    }
    while (dummy_b->parent != nullptr){
      dummy_b = dummy_b->parent;
      depth_b++;
    }

    return depth_a > depth_b ? findlca(a->parent, b) : depth_a == depth_b ? findlca(a->parent,b->parent): findlca(a,b->parent);
  }
}