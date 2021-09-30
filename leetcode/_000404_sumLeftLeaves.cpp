/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int sumLeftInternal(TreeNode* root, bool amILeft) {
        if (root->left == nullptr && root->right == nullptr) {
            return (amILeft ? root->val : 0);
        }
        int sum = 0;
        if (root->left) {
            sum += sumLeftInternal(root->left, true);
        }
        if (root->right) {
            sum += sumLeftInternal(root->right, false);
        }
        return sum;
    }
    
    int sumOfLeftLeaves(TreeNode* root) {
        return sumLeftInternal(root, false);
    }
};
