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
        // Note that at least one of give or need will always be 0.
        int give=0;  // total coins that this subtree can give
        int need=0;  // total coins needed by this subtree
        int cost=0;  // cumulative cost incurred by this subtree (including child trees)
    };
public:
    Info traverse(TreeNode* root) {
        if (root == nullptr) return {0, 0, 0};
        if (root->left == nullptr && root->right == nullptr) {
            if (root->val == 0) return {0, 1, 0};
            if (root->val == 1) return {0, 0, 0};
            return {root->val-1, 0, 0};
        }
        
        Info lhs = traverse(root->left);
        Info rhs = traverse(root->right);
        
        int left_cost = std::max(lhs.give, lhs.need) + lhs.cost;
        int right_cost = std::max(rhs.give, rhs.need) + rhs.cost;
        int my_give = root->val + lhs.give + rhs.give;
        int my_need = 1 + lhs.need + rhs.need;
        
        if (my_give > my_need) {
            return {my_give-my_need, 0, left_cost+right_cost};
        }
        return {0, my_need-my_give, left_cost+right_cost};
    }
    
    int distributeCoins(TreeNode* root) {
        Info info = traverse(root);
        return info.cost;
    }
};
