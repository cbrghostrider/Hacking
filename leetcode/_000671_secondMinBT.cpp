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
    int findSecondMin(TreeNode* root, int min) {
        if (!root->left && !root->right) {
            return root->val == min ? -1 : root->val;
        }
        if (!root->left) return findSecondMin(root->right, min);
        if (!root->right) return findSecondMin(root->left, min);
        int second_min_left = (root->left->val == min) ? findSecondMin(root->left, min) : root->left->val;
        int second_min_right = (root->right->val == min) ? findSecondMin(root->right, min) : root->right->val;
        if (second_min_left == -1) return second_min_right;
        if (second_min_right == -1) return second_min_left;
        return std::min(second_min_left, second_min_right);
    }
    
    int findSecondMinimumValue(TreeNode* root) {
        return findSecondMin(root, root->val);
    }
};
