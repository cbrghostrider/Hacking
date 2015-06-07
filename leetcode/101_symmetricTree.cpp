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
    bool traverseTreesSymmetric(TreeNode *left, TreeNode *right) {
        if (left == NULL && right == NULL) return true;
        if (left == NULL || right == NULL) return false;
        if (left->val != right->val) return false;
        bool llhsrrhs = traverseTreesSymmetric(left->left, right->right);
        bool lrhsrlhs = traverseTreesSymmetric(left->right, right->left);
        return (llhsrrhs && lrhsrlhs);
    }
public:
    bool isSymmetric(TreeNode* root) {
        return (root == NULL || traverseTreesSymmetric(root->left, root->right));
    }
};
