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
    int sum = 0;
    int lowVal = 0;
    int highVal = 0;
    
    void traverse(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        
        if (root->val > lowVal) {
            traverse(root->left);
        }
        
        if (lowVal <= root->val && root->val <= highVal) {
            sum += root->val;
        }
        
        if (root->val < highVal) {
            traverse(root->right);
        }
    }
    
    int rangeSumBST(TreeNode* root, int low, int high) {
        lowVal = low;
        highVal = high;
        traverse(root);
        return sum;
    }
};
