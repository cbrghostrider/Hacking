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
    
    // returns the sum of everything in this subtree
    // entry_val is the sum of everything greater than this root, coming from parent
    int traverse(TreeNode* root, int entry_val) {
        if (root == nullptr) return 0;
        
        int rhs = traverse(root->right, entry_val);
        int my_val = root->val + rhs + entry_val;
        int lhs = traverse(root->left, my_val);
        
        int retval = rhs + lhs + root->val;
        root->val = my_val;
        return retval;
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        traverse(root, 0);
        return root;
    }
};
