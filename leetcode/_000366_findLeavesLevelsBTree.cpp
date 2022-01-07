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
    map<int, vector<int>> seq;
    
    int traverse(TreeNode* node) {
        if (node == nullptr) return 0;
        int lhs = traverse(node->left);
        int rhs = traverse(node->right);
        int my_level = std::max(lhs, rhs) + 1;
        seq[my_level].push_back(node->val);
        return my_level;
    }
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        traverse(root);
        vector<vector<int>> ans;
        for (const auto& kv : seq) {
            ans.push_back(kv.second);
        }
        return ans;        
    }
};
