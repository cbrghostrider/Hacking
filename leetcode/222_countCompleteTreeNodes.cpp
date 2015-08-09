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
    int heightLHS(TreeNode* root) {
        if (root == nullptr) return 0;
        return (1 + heightLHS(root->left));
    }
    int heightRHS(TreeNode* root) {
        if (root == nullptr) return 0;
        return (1 + heightRHS(root->right));
    }
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        int lhsht = heightLHS(root);
        int rhsht = heightRHS(root);
        if (lhsht == rhsht) { //full tree
            return ((1 << (lhsht)) - 1);
        }
        return (1 + countNodes(root->left) + countNodes(root->right));
    }
};
