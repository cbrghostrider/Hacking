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
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return root;
        TreeNode* newleft  = invertTree(root->right);
        TreeNode* newright = invertTree(root->left);
        root->left = newleft;
        root->right = newright;
        return root;
    }
};
