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
    vector<int> sig1, sig2;
public:
    void sequence(vector<int>& seq, TreeNode *root) {
        if (root == nullptr) {return;}
        if (root->left == nullptr && root->right == nullptr) {seq.push_back(root->val);}
        sequence(seq, root->left);
        sequence(seq, root->right);
    }
    
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        sequence(sig1, root1);
        sequence(sig2, root2);
        return (sig1 == sig2);
    }
};
