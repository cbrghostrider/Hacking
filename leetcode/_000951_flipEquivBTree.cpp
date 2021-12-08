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
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if (root1 == nullptr && root2 == nullptr) return true;
        if (root1 == nullptr || root2 == nullptr) return false;
        if (root1->val != root2->val) return false;
        
        // I either flip this node
        bool lhs1 = flipEquiv(root1->left, root2->right);
        bool rhs1 = flipEquiv(root1->right, root2->left);
        
        // Or I don't flip this node
        bool lhs2 = flipEquiv(root1->left, root2->left);
        bool rhs2 = flipEquiv(root1->right, root2->right);
        
        return ((lhs1 && rhs1) || (lhs2 && rhs2));
    }
};
