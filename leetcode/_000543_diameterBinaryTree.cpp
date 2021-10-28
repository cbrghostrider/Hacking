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
    int longest = 0;
    
public:
    
    // returns height of tree rooted here
    int dfs(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        int height_left = (root->left == nullptr) ? 0 : dfs(root->left) + 1;
        int height_right = (root->right == nullptr) ? 0 : dfs(root->right) + 1;
        int longest_local = height_left + height_right;
        if (longest_local > longest) {
            longest = longest_local;
        }
        return std::max(height_left, height_right);
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return longest;
    }
};
