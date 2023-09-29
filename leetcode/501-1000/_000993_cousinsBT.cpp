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
        int depth;
        int parent_val;
    };
    
    Info* search(TreeNode* root, int val, int parent_val, int parent_depth) {
        if (root == nullptr) return nullptr;
        if (root->val == val) { return new Info{parent_depth + 1, parent_val}; }
        Info* left = search(root->left, val, root->val, parent_depth+1);
        if (left != nullptr) return left;
        return search(root->right, val, root->val, parent_depth+1);
    }
    
public:
    bool isCousins(TreeNode* root, int x, int y) {
        Info *x_info = search(root, x, -1, -1);
        Info *y_info = search(root, y, -1, -1);
        bool ret = false;
        if (x_info != nullptr && y_info != nullptr) {
            ret = (x_info->depth == y_info->depth) && (x_info->parent_val != y_info->parent_val);
        }
        delete x_info;
        delete y_info;
        return ret;
    }
};
