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
public:
    vector<int> largestValues(TreeNode* root) {
        if (root == nullptr) return {};
        
        // (node, level)
        std::queue<std::pair<TreeNode*, int>> q;
        q.push({root, 0});
        
        vector<int> ans;
        int last_level=-1;
        
        while (!q.empty()) {
            pair<TreeNode*, int> vl = q.front();
            q.pop();
            if (last_level != vl.second) {
                ans.push_back(vl.first->val);
                last_level = vl.second;
            }
            
            if (ans[last_level] < vl.first->val) {
                ans[last_level] = vl.first->val;
            }
            
            if (vl.first->left) {q.push({vl.first->left, vl.second+1});}
            if (vl.first->right) {q.push({vl.first->right, vl.second+1});}
        }        
        return ans;
    }
};
