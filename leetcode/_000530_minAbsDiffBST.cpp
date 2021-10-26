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
    int lastVal = std::numeric_limits<int>::min();
    int minAbsDiff = std::numeric_limits<int>::max();
    
    void traverse(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        
        traverse(root->left);
        
        if (init == false) {
            init = true;
            lastVal = root->val;
        } else {
            int absDiff = abs(lastVal - root->val);
            if (absDiff < minAbsDiff) {
                minAbsDiff = absDiff;
            }
            lastVal = root->val;
        }
        
        traverse(root->right);
    }
    
    int getMinimumDifference(TreeNode* root) {
        traverse(root);
        return minAbsDiff;
    }
};
