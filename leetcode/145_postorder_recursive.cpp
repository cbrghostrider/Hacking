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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> retval;
        if (root == NULL) return retval;
        retval = postorderTraversal(root->left);
        vector<int> rhs = postorderTraversal(root->right);
        if (rhs.size() > 0) retval.insert(retval.end(), rhs.begin(), rhs.end());
        retval.push_back(root->val);
        return retval;
    }
};
