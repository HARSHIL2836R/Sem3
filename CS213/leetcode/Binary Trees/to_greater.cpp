
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
    int sum = 0;
    void to_greater(TreeNode* root) {
        if (!root) return;
        to_greater(root->right);
        sum+= root->val;
        root->val = sum;
        to_greater(root->left);
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        to_greater(root);
        return root;
    }
};