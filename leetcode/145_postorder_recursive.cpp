// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
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
