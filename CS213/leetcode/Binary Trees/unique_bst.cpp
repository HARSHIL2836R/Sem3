/*Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
};
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
}
#include <bits/stdc++.h>
using namespace std;

vector<TreeNode*> generateSubtrees(int s, int e) {
	vector<TreeNode*> res;
	if (s > e) {
		res.push_back(nullptr); // empty tree
		return res;
	}

	for (int i = s; i <= e; ++i) {
		vector<TreeNode*> leftSubtrees = generateSubtrees(s, i - 1);
		vector<TreeNode*> rightSubtrees = generateSubtrees(i + 1, e);

		for (TreeNode* left : leftSubtrees) {
			for (TreeNode* right : rightSubtrees) {
				TreeNode* root = new TreeNode(i);
				root->left = left;
				root->right = right;
				res.push_back(root);
			}
		}
	}
	return res;
}
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
	    return generateSubtrees(1, n);
    }
};