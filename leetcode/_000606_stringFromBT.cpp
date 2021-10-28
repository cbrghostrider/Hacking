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
    string answer;
    
    void preorder(TreeNode* root) {
        if (root == nullptr) return;
        
        answer += std::to_string(root->val);
        if (!root->left && !root->right) return;
        
        answer.push_back('(');
        preorder(root->left);
        answer.push_back(')');
        
        if (root->right) {
            answer.push_back('(');
            preorder(root->right);
            answer.push_back(')');
        }
        
    }
    
    string tree2str(TreeNode* root) {
        preorder(root);
        return answer;
    }
};
