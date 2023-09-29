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
    int bstSize(TreeNode *root) {
        if (root == nullptr) return 0;
        return (1 + bstSize(root->left) + bstSize(root->right));
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        if (root == nullptr) return 0; //error case really
        int bstsizelhs = bstSize(root->left);
        if (k == (bstsizelhs + 1)) return root->val; //found you!
        if (k <= bstsizelhs) return kthSmallest(root->left, k);
        return kthSmallest(root->right, k-(bstsizelhs+1));
    }
};
