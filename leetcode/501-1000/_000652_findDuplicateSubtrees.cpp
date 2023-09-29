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
    unordered_map<string, pair<TreeNode*, int>> signatures;
    
    string traverse(TreeNode* root) {
        if (root == nullptr) return "N;";
        string my_sig = to_string(root->val) + ";";
        my_sig += traverse(root->left);
        my_sig += traverse(root->right);
        if (signatures.find(my_sig) != signatures.end()) {
            auto& elem = signatures[my_sig];
            elem.second++;
        } else {
            signatures[my_sig] = {root, 1};
        }
        return my_sig;
    }
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        if (root == nullptr) return {nullptr};
        traverse(root);
        vector<TreeNode*> ans;
        for (const auto& kv : signatures) {
            if (kv.second.second == 1) continue;
            ans.push_back(kv.second.first);
        }
        return ans;
    }
};
