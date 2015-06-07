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
// The maximum depth is the number of nodes along the longest path from the 
// root node down to the farthest leaf node
//
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL) return 0;
        if (root->left == NULL)  return (1 + maxDepth(root->right));
        if (root->right == NULL) return (1 + maxDepth(root->left));
        return (1 + max(maxDepth(root->left), maxDepth(root->right)));
    }
};
