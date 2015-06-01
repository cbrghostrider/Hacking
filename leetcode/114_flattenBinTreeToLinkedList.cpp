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
    void flatten(TreeNode* root) {
        if (root == NULL) return;
        TreeNode* lhs = root->left;
        TreeNode* rhs = root->right;
        flatten(lhs);
        flatten(rhs);
        root->left = NULL;
        if (lhs) {
            root->right = lhs;
            while (lhs->right) {
                lhs = lhs->right;
            }
            lhs->right = rhs;
        }
    }
};
