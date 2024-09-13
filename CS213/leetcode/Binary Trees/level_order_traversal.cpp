/**
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> prev_parent;
        queue<TreeNode*> parent;
        vector<vector<int>> result;
        prev_parent.push(root);
        do{
            if (root) {result.push_back(vector<int>());}
            while (prev_parent.size() > 0) {
                TreeNode* curr = prev_parent.front();
                prev_parent.pop();
                if (!curr) break;
                result.back().push_back(curr->val);
                if (curr->left) parent.push(curr->left);
                if (curr->right) parent.push(curr->right);
            }
            prev_parent = parent;
            while (!parent.empty()) parent.pop();
        }
        while (prev_parent.size() > 0);
        return result;
    }
};