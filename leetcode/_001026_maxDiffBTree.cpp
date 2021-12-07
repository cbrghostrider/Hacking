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
    struct Info {
        int max=0;
        int min=0;
        int v=0;
        bool valid = false;
    };
    
    Info maxAncestor(TreeNode* root) {
        if (root == nullptr) return {0, 0, 0, false};
        if (root->left == nullptr && root->right == nullptr) {
            return {root->val, root->val, 0, true};
        }
        
        Info lhs = maxAncestor(root->left);
        Info rhs = maxAncestor(root->right);
        
        int max_child = lhs.valid ? (rhs.valid ? std::max(lhs.max, rhs.max) : lhs.max) : rhs.max;
        int min_child = lhs.valid ? (rhs.valid ? std::min(lhs.min, rhs.min) : lhs.min) : rhs.min;
        int my_v = std::max(std::abs(root->val - max_child), std::abs(root->val - min_child));
        int child_v = std::max(lhs.valid ? lhs.v : 0, rhs.valid ? rhs.v : 0);
        
        return {std::max(root->val, max_child), std::min(root->val, min_child), 
                std::max(my_v, child_v), true};
    }
    
public:
    int maxAncestorDiff(TreeNode* root) {
        Info info = maxAncestor(root);
        return info.v;
    }
};
