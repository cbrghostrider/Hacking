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
    bool init = false;
    int lastNum = 0;
    int minDiff = std::numeric_limits<int>::max();
    
    void traverse(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        traverse(root->left);
        
        int diff = root->val - lastNum;
        lastNum = root->val;
        
        if (init == false) {
            init = true;
        } else if (diff < minDiff) {
            minDiff = diff;
        }
        
        traverse(root->right);
    }
    
    int minDiffInBST(TreeNode* root) {
        traverse(root);
        return minDiff;
    }
};
