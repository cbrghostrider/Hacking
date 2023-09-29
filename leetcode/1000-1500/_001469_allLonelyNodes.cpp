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
    vector<int> ans;
    void traverse(TreeNode* root) {
        if (root == nullptr) return;
        if (root->left == nullptr && root->right == nullptr) return;
        if (root->left == nullptr) { ans.push_back(root->right->val); }
        if (root->right == nullptr) { ans.push_back(root->left->val); }
        traverse(root->left);
        traverse(root->right);
    }
    
public:
    vector<int> getLonelyNodes(TreeNode* root) {
        traverse(root);
        return ans;
    }
};
