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
    vector<int> csums;
public:
    void traverse(TreeNode* node, int level) {
        if (node == nullptr) return;
        if (csums.size() <= level) csums.push_back(0);
        csums[level] += node->val;
        traverse(node->left,  level+1);
        traverse(node->right, level+1);
    }

    void replace(TreeNode* node, int level, int sub) {
        if (node == nullptr) return;
        node->val = csums[level] - sub;
        int my_sub = 0;
        if (node->left) my_sub += node->left->val;
        if (node->right) my_sub += node->right->val;
        replace(node->left,  level+1, my_sub);
        replace(node->right, level+1, my_sub);
    }
    TreeNode* replaceValueInTree(TreeNode* root) {
        traverse(root, 0);
        replace(root, 0, root->val);
        return root;
    }
};