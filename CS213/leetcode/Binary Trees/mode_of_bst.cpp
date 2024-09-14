#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
vector<pair<int, int>> ino;
void inorder(TreeNode* root) {
    if (!root)
        return;
    inorder(root->left);
    if (ino.size()>0 && (ino.back()).first == root->val) {
        int freq = (ino.back()).second + 1;
        ino.pop_back();
        ino.push_back({root->val, freq});
    } else
        ino.push_back({root->val, 1});
    inorder(root->right);
}
class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        vector<int> result;
        ino.clear();
        inorder(root);
        if (ino.size() == 0) return result;
        auto comp = [](pair<int, int> a, pair<int, int> b) { // LAMBDA FUNCTION
            return a.second > b.second;
        };
        sort(ino.begin(), ino.end(), comp);
        int max_el = ino.front().second;
        auto itr = ino.begin();
        while (itr!=ino.end() && (*itr).second == max_el) {
            result.push_back((*itr).first);
            ++itr;
        }
        return result;
    }
};

/*
Better Off here
class Solution {
    TreeNode* prev = NULL;
    int count = 0;
    int max_count = 0;

    void bst(TreeNode* node, vector<int>& result) {
        if (!node) {
            return;
        }

        bst(node->left, result);

        if (prev && prev->val == node->val) {
            ++count;
        } else {
            count = 1;
        }

        if (count > max_count) {
            max_count = count;
            result.clear();
            result.emplace_back(node->val);
        } else if (count == max_count) {
            result.emplace_back(node->val);
        }

        prev = node;
        bst(node->right, result);
    }

public:
    vector<int> findMode(TreeNode* root) {
        vector<int> result;
        result.reserve(10'000);
        bst(root, result);
        return result;
    }
};
*/