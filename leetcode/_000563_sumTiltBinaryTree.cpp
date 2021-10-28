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
    int sum_tilt = 0;
    
    int sumTree(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int sum_left = sumTree(root->left);
        int sum_right = sumTree(root->right);
        int local_tilt = std::abs(sum_left - sum_right);
        sum_tilt += local_tilt;
        return sum_left + root->val + sum_right;
    }
    
    int findTilt(TreeNode* root) {
        sumTree(root);
        return sum_tilt;
    }
};
