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
    vector<string> binaryTreePaths(TreeNode* root) {
        if (root == NULL) return vector<string>();
        if (root->left == NULL && root->right == NULL) {
            return vector<string>(1, to_string(root->val));
        } 
        vector<string> retval, lhsstrs, rhsstrs;
        if (root->left) lhsstrs = binaryTreePaths(root->left);
        if (root->right) rhsstrs = binaryTreePaths(root->right);
        retval.insert(retval.end(), lhsstrs.begin(), lhsstrs.end());
        retval.insert(retval.end(), rhsstrs.begin(), rhsstrs.end());
        for (string& str : retval) str = to_string(root->val) + "->" + str;
        return retval;
    }
};

