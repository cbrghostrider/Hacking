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
        TreeNode* subtree = nullptr;  // subtree candidate for this recursive call
        int depth = 0;                // max depth on this recursive call
    };
    
    Info traverse(TreeNode* root) {
        if (root == nullptr) return {nullptr, 0};
        Info lhs = traverse(root->left);
        Info rhs = traverse(root->right);
        if (lhs.depth == rhs.depth) {
            return {root, lhs.depth+1};
        }
        if (lhs.depth > rhs.depth) {
            return {lhs.subtree, lhs.depth+1};
        }
        return {rhs.subtree, rhs.depth+1};
    }
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        Info info = traverse(root);
        return info.subtree;
    }
};
