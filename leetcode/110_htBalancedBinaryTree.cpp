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
