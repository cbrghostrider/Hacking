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

void addOneRow(TreeNode* cur_node, int cur_depth, int val, int depth) {
    if (cur_node == nullptr) { return; }
    if (cur_depth == depth-1) {
        TreeNode* new_left  = new TreeNode(val);
        TreeNode* new_right = new TreeNode(val);
        if (cur_node->left)  { new_left->left = cur_node->left; }
        if (cur_node->right) { new_right->right = cur_node->right; }
        cur_node->left = new_left;
        cur_node->right = new_right;
        return;
    }
    addOneRow(cur_node->left, cur_depth+1, val, depth);
    addOneRow(cur_node->right, cur_depth+1, val, depth);
}

public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if (depth == 1) {
            TreeNode *node = new TreeNode(val);
            node->left = root;
            return node;
        }
        addOneRow(root, 1, val, depth);
        return root;
    }
};
