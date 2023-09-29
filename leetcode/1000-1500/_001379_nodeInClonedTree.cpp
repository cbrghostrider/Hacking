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
public:
    vector<char> choices;
    bool find(TreeNode* root, TreeNode* clone) {
        if (root == nullptr || clone == nullptr) return false;
        if (root->val == clone->val) return true;
        
        choices.push_back('L');
        bool left_check = find(root->left, clone);
        if (left_check) return true;
        
        choices.pop_back();
        choices.push_back('R');
        bool right_check = find(root->right, clone);
        if (right_check) return true;
        
        choices.pop_back();
        return false;
    }
    
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        if (find(original, target) == false) return nullptr;  // cloned isn't in the original tree
        
        TreeNode *node = cloned;
        for (int i=0; i<choices.size(); i++) {
            if (choices[i] == 'L') {node = node->left;}
            else {node = node->right;}
        }
        return node;
    }
};
