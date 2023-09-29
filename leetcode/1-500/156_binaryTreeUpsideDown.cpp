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
    TreeNode *newroot = nullptr;
    
    void upsideDownBT(TreeNode *nroot, TreeNode *prevParent, TreeNode *prevRight) {
        if (nroot->left == NULL) {
            newroot = nroot;
        } else {
            upsideDownBT(nroot->left, nroot, nroot->right);
        }
        nroot->left  = prevRight;
        nroot->right = prevParent;
    }
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (root == NULL) return NULL;
        if (root->left == NULL) return root;
        upsideDownBT(root->left, root, root->right);
        root->left = root->right = NULL;
        return newroot;
    }
};
