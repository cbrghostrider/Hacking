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
        int sum=0;
        int num=0;
        double max_avg=0;
    };
    
    Info traverse(TreeNode* root) {
        if (root == nullptr) return {0, 0, 0};
        Info lhs = traverse(root->left);
        Info rhs = traverse(root->right);
        int my_sum = root->val + lhs.sum + rhs.sum;
        int my_num = 1 + lhs.num + rhs.num;
        double my_avg = ((double)my_sum) / my_num;
        return {my_sum, my_num, std::max(std::max(lhs.max_avg, rhs.max_avg), my_avg)};
    }
public:
    double maximumAverageSubtree(TreeNode* root) {
        Info info = traverse(root);
        return info.max_avg;
    }
};
