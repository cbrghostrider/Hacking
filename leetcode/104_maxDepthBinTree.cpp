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
