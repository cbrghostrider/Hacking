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
    vector<vector<string>> ans;
    int H, C;
    
    int getHeight(TreeNode* node) {
        if (node == nullptr) {return 0;}
        int lhs = 1 + getHeight(node->left);
        int rhs = 1 + getHeight(node->right);
        return std::max(lhs, rhs);
    }
    
    void place(TreeNode* node, int my_row, int my_col) {
        if (node == nullptr) return;        
        ans[my_row][my_col] = to_string(node->val);
        
        int child_row = my_row + 1;
        int part = H-my_row-1;
        part = part < 0 ? 0 : part;
        int lhs_col = my_col - (1 << (part));
        int rhs_col = my_col + (1 << (part));
        
        place(node->left,  child_row, lhs_col);
        place(node->right, child_row, rhs_col);
    }
    
public:
    vector<vector<string>> printTree(TreeNode* root) {
        if (root == nullptr) return {};
        
        H = getHeight(root) - 1;
        C = (1 << (H+1)) - 1;
        ans = vector<vector<string>>(H+1, vector<string>(C, ""));
                
        place(root, 0, (C-1)/2);
        return ans;
    }
};
