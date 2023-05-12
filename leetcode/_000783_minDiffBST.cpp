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
        int max = 0;
        int min = 0;
    };
    pair<Info, int> traverse(TreeNode* root) {
        if (root == nullptr) {
            return make_pair(Info{-1, -1}, std::numeric_limits<int>::max());
        }
        auto lhs = traverse(root->left);
        auto rhs = traverse(root->right);
        int cand = std::numeric_limits<int>::max();

        if (lhs.first.max != -1) {
            cand = std::min(cand, std::abs(root->val - lhs.first.max));
            cand = std::min(lhs.second, cand);
        }
        if (rhs.first.min != -1) {
            cand = std::min(cand, std::abs(root->val - rhs.first.min));
            cand = std::min(rhs.second, cand);
        }
        Info ret_first;
        ret_first.min = lhs.first.min == -1 ? root->val : lhs.first.min;
        ret_first.max = rhs.first.max == -1 ? root->val : rhs.first.max;
        return make_pair(ret_first, cand);
    }
public:
    int minDiffInBST(TreeNode* root) {
        auto ans = traverse(root);
        return ans.second;
    }
};