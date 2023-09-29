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
        TreeNode *lca=nullptr;
        int ht=0;
    };
    Info lcaDeep(TreeNode* root) {
        if (root == nullptr) return {nullptr, 0};
        if (root->left == nullptr && root->right == nullptr) {
            return {root, 1};
        }
        Info info_l = lcaDeep(root->left);
        Info info_r = lcaDeep(root->right);
        if (info_l.ht == info_r.ht) {
            return {root, info_l.ht+1};
        }
        return {info_l.ht < info_r.ht ? info_r.lca  : info_l.lca,
                info_l.ht < info_r.ht ? info_r.ht+1 : info_l.ht+1};
    }
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        Info info = lcaDeep(root);
        return info.lca;
    }
};
