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
    // outer key: col
    // inner key: row
    // val: ordered set of values at that cell
    map<int, map<int, multiset<int>>> vals;
    
    void populate(TreeNode* node, int my_row, int my_col) {
        if (node == nullptr) return;
        vals[my_col][my_row].insert(node->val);
        populate(node->left, my_row+1, my_col-1);
        populate(node->right, my_row+1, my_col+1);
    }
public:
    // O(n) time, O(n) space.
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        populate(root, 0, 0);
        
        vector<vector<int>> ans;
        for (const auto& kv : vals) {  // key col
            ans.push_back({});
            auto& vec = ans.back();
            
            for (const auto& kv2 : kv.second) {  // key row                
                vec.insert(vec.end(), kv2.second.begin(), kv2.second.end());
            }
        }
        return ans;
    }
};
