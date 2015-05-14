/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    TreeNode* sortedArrayToBST_(vector<int>& nums, int from, int to) {
        if (from > to) return NULL;
        int midpt = (from + to)/2;
        TreeNode *root = new TreeNode(nums[midpt]);
        if (from == to) return root;
        root->left  = sortedArrayToBST_(nums, from, midpt-1);
        root->right = sortedArrayToBST_(nums, midpt+1, to);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.size() == 0) return NULL;
        return sortedArrayToBST_(nums, 0, nums.size()-1);
    }
};
