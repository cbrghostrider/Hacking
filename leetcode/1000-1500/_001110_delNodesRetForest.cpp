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
    unordered_set<int> deletes;
    unordered_set<TreeNode*> roots;
    
    void descend(TreeNode* root, TreeNode* from) {
        if (root == nullptr) return;
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        if (deletes.find(root->val) != deletes.end()) {
            roots.erase(root);
            if (left) roots.insert(left);
            if (right) roots.insert(right);
            if (from &&from->left == root) {from->left = nullptr;}
            if (from && from->right == root) {from->right = nullptr;}
            delete root;
            root = nullptr;
        }
        descend(left, root);
        descend(right, root);
    }
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        for (int i : to_delete) {deletes.insert(i);}
        roots.insert(root);
        descend(root, nullptr);
        vector<TreeNode*> ans;
        for (TreeNode* node : roots) {ans.push_back(node);}
        return ans;
    }
};
