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
    // breaks up root into two subtress (<target, >target)
    pair<TreeNode*, TreeNode*> descend(TreeNode* root, int target) {
        if (root == nullptr) return {nullptr, nullptr} ;
        
        if (root->val == target) {
            TreeNode* right = root->right;
            root->right = nullptr;
            return {root, right};
        }
        
        if (root->val > target) {  
            // recurse left
            auto lhs = descend(root->left, target);
            root->left = lhs.second;
            return {lhs.first, root};
        }
        
        // recurse right
        auto rhs = descend(root->right, target);
        root->right = rhs.first;
        return {root, rhs.second};
    }
public:
    vector<TreeNode*> splitBST(TreeNode* root, int target) {
        auto vals = descend(root, target);
        return {vals.first, vals.second};
    }
};
