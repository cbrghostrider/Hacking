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
        int seq_me=0;    // Sequence that includes my node
        int seq_deep=0;  // A deeper sequence not including my node
    };
    
    // O(n) time, O(n) space for dfs.
    Info dfs(TreeNode* root) {
        if (root == nullptr) return {0, 0};
        
        Info lhs = dfs(root->left);
        Info rhs = dfs(root->right);
        
        int lhs_me=0, rhs_me=0;
        int lhs_deep=0, rhs_deep=0;
        
        if (root->left && root->left->val == root->val+1)  {
            lhs_me = 1 + lhs.seq_me;
        } else {
            lhs_deep = std::max(lhs.seq_deep, lhs.seq_me);
        }
        if (root->right && root->right->val == root->val+1) {
            rhs_me = 1 + rhs.seq_me;
        } else {
            rhs_deep = std::max(rhs.seq_deep, rhs.seq_me);
        }
        
        return {std::max(lhs_me, rhs_me), std::max(lhs_deep, rhs_deep)};
    }
public:
    int longestConsecutive(TreeNode* root) {
        Info info = dfs(root);
        
        // Note that the seq returned is actually the number of "edges"
        // To convert it to number of nodes, we add the ending node
        return 1 + std::max(info.seq_me, info.seq_deep);
    }
};
