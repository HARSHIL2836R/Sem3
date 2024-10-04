#include "tree.h"

/* You should NOT add ANY other includes to this file.
 * Your task is to implement the "encode_tree" function as described
 * in the file "tree.h". Read the instructions there.
 * */

/*

This function prints the TREE using ASCII characters using the
  // format:
  //
  //   root
  //       |-- left subtree
  //       |__ right subtree
  //
  // where the left and right subtrees are printed recursively in
  // the same format.

|__1
    |__2
        |--4
        |__3
            |__5

Our Encoded String is:
(<1<(<2<(<4<>>)>>)(<3<(<5<>>)>>)>>)

*/

// Helper function to encode the tree recursively
template <size_t N = 0>
std::string encode(std::shared_ptr<node_t> root, std::string& result){
    std::shared_ptr<node_t> fixed_root = root;
    auto n_ary_root = std::dynamic_pointer_cast<n_ary_node_t>(root);
    //std::dynamic_pointer_cast<fixed_node_t>(fixed_root);

    if (root != nullptr && n_ary_root != nullptr){
        result += "<" + std::to_string(n_ary_root->val) + "<";
        for (size_t i = 0; i < n_ary_root->children.size(); ++i) {
            encode(n_ary_root->children[i], result);
        }
        result += ">>";
    }
    return result;
}
std::string encode_tree(std::shared_ptr<node_t> root) {
    // TODO: Write your code here
    std::string result;
    encode(root, result);
    std::cout<<result<<std::endl;
    return result; // dummy return
    // End TODO
}