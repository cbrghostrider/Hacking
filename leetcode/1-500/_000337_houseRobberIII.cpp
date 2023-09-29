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
    unordered_map<string, int> cache;
    
    string signature(TreeNode* root, int level, bool rob_level) {
        return (to_string(reinterpret_cast<uint64_t>(root)) + "-" + to_string(level) + "-" + (rob_level ? "Y":"N"));
    }
    
    int robInternal(TreeNode* root, int level, bool rob_level) {
        if (root == nullptr) return 0;
        string sig = signature(root, level, rob_level);
        if (cache.find(sig) != cache.end()) return cache[sig];
        
        int val1 = rob_level? root->val : 0;
        val1 += robInternal(root->left, level + 1, !rob_level);
        val1 += robInternal(root->right, level + 1, !rob_level);
        
        int val2 = 0;   // even if possible to rob, I won't
        val2 += robInternal(root->left, level + 1, true);
        val2 += robInternal(root->right, level + 1, true);
        
        cache[sig] = std::max(val1, val2);
        return cache[sig];
    }
public:
    int rob(TreeNode* root) {
        int r1 = robInternal(root, 0, true);
        int r2 = robInternal(root, 0, false);
        return std::max(r1, r2);
    }
};
