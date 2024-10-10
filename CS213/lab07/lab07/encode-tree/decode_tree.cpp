#include "tree.h"

/* You should NOT add ANY other includes to this file.
 * Your task is to implement the "encode_tree" function as described
 * in the file "tree.h". Read the instructions there.
 * */

std::shared_ptr<n_ary_node_t> decode(std::string encoded) {
    if(*encoded.begin() == '<'){
            // Create a new n-ary node
            std::shared_ptr<n_ary_node_t> node = std::make_shared<n_ary_node_t>();
            // Read the value of the node
            node->val = std::stoi(encoded.substr(1, encoded.find('<') - 1));
            encoded = encoded.substr(encoded.find('<') + 1);

            // Read and create children recursively
            while (encoded.find('<')!= std::string::npos) {
                std::shared_ptr<n_ary_node_t> child = decode(encoded);
                node->children.push_back(child);
                encoded = encoded.substr(encoded.find('<') + 1);
            }

            return node;
    }
}
std::shared_ptr<node_t> decode_tree(std::string encoded) {
    // TODO: Write your code here
    auto root = decode(encoded);
    return root;
    // End TODO
}