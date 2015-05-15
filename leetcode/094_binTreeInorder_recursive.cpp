/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> retval;
        if (root == NULL) return retval;
        vector<int> lhs = inorderTraversal(root->left);
        vector<int> rhs = inorderTraversal(root->right);
        retval = lhs;
        retval.push_back(root->val);
        retval.insert(retval.end(), rhs.begin(), rhs.end());
        return retval;
    }
};
