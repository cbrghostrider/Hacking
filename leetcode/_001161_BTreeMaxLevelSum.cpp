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
    // O(n) space, O(n) time.
    int maxLevelSum(TreeNode* root) {
        if (root == nullptr) return 0;
        
        int max=std::numeric_limits<int>::min();
        int sum=0;
        int maxlevel=0;
        // queue of (node, level)
        std::queue<pair<TreeNode*, int>> q;
        q.push({root, 1});
        
        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            
            sum += node.first->val;
            if (node.first->left)  q.push({node.first->left,  node.second+1});
            if (node.first->right) q.push({node.first->right, node.second+1});
            
            if (q.empty() || q.front().second != node.second) {
                if (sum > max) {
                    max = sum;
                    maxlevel = node.second;
                }
                sum = 0;
            }
        }
        return maxlevel;
    }
};
