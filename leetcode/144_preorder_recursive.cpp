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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> retval;
        if (root == NULL) return retval;
        retval.push_back(root->val);
        vector<int> lhs = preorderTraversal(root->left);
        vector<int> rhs = preorderTraversal(root->right);
        if (lhs.size() > 0) retval.insert(retval.end(), lhs.begin(), lhs.end());
        if (rhs.size() > 0) retval.insert(retval.end(), rhs.begin(), rhs.end());
        return retval;
    }
};
