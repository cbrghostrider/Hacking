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
    // carryOver is the value passed by parent when it calls this function.
    // it is the sum of everything greater than root (including parent if needed) not including subtree at root
    // return value is sum of values in tree rooted at root
    int bstToGst_(TreeNode* root, int carry_over) {
        if (root == nullptr) return 0;
        int my_rhs_sum = bstToGst_(root->right, carry_over);
        int new_carry_over = carry_over + my_rhs_sum + root->val;
        int my_lhs_sum = bstToGst_(root->left, new_carry_over);
        int ret = (my_rhs_sum + root->val + my_lhs_sum);
        root->val = carry_over + my_rhs_sum + root->val;
        return ret;
    }
    
public:
    TreeNode* bstToGst(TreeNode* root) {
        bstToGst_(root, 0);
        return root;
    }
};
