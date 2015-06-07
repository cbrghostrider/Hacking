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
//
// For this problem, a height-balanced binary tree is defined as a binary tree 
// in which the depth of the two subtrees of *every* node never differ by more than 1
//
class Solution {
    //sets height to -1 if unbalanced, so that it can be propagated up
    int getHeightAndCheckBalance(TreeNode *root) {
        if (root == NULL) return 0;
        int htlhs = getHeightAndCheckBalance(root->left);
        int htrhs = getHeightAndCheckBalance(root->right);
        return ((htlhs == -1 || htrhs == -1) ? -1 : ((abs(htlhs - htrhs) <= 1) ? 1 + max(htlhs, htrhs) : -1));
    }
public:
    bool isBalanced(TreeNode* root) {
        return (getHeightAndCheckBalance(root) != -1);
    }
};
