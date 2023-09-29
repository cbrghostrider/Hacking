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
    
    // returns (sum, num), where:
    // sum is sum of all the nodes in the tree
    // num is the number of nodes in the tree that satisfy the answer
    pair<long, int> sumNumNodes(TreeNode* node) {
        if (node == nullptr) return make_pair(0, 0);
        if (node->left == nullptr && node->right == nullptr) {
            return make_pair(node->val, node->val == 0 ? 1 : 0);
        }
        pair<long, int> lhs = sumNumNodes(node->left);
        pair<long, int> rhs = sumNumNodes(node->right);
        
        long sum_desc = lhs.first+rhs.first;
        long my_sum = sum_desc + node->val;
        int me_if_needed = node->val == sum_desc ? 1 : 0;
        int my_num = lhs.second + rhs.second + me_if_needed;
        return make_pair(my_sum, my_num);
    }
public:
    int equalToDescendants(TreeNode* root) {
        pair<long, int> sn = sumNumNodes(root);
        return sn.second;
    }
};
