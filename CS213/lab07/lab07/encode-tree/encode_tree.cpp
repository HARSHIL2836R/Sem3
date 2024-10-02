#include "tree.h"

/* You should NOT add ANY other includes to this file.
 * Your task is to implement the "encode_tree" function as described
 * in the file "tree.h". Read the instructions there.
 * */

/*
<1<2<4<5>>><3>>

*/

// Helper function to encode the tree recursively
template <size_t N = 0>
std::string encode(std::shared_ptr<node_t> root, std::string& result){
    std::shared_ptr<node_t> n_ary_root = root;
    std::shared_ptr<node_t> fixed_root = root;
    std::dynamic_pointer_cast<n_ary_node_t>(n_ary_root);
    //std::dynamic_pointer_cast<fixed_node_t>(fixed_root);

    if (root != nullptr && n_ary_root != nullptr && fixed_root == nullptr){
        result += "<" + std::to_string(n_ary_root->val) + "<";
        for (size_t i = 0; i < n_ary_root->children.size(); ++i) {
            encode(n_ary_root->children[i], result);
        }
        result += ">>";
    }
}
std::string encode_tree(std::shared_ptr<node_t> root) {
    // TODO: Write your code here
    std::string result;
    encode(root, result);
    return result; // dummy return
    // End TODO
}