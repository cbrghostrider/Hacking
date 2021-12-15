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
    // returns true if found in my subtree, 
    // if true is returned, then it also adds root to the path
    bool findNode(TreeNode* root, TreeNode* find, vector<TreeNode*>& stack) {
        if (root == nullptr || find == nullptr) return false;
        if (root == find) {
            stack.push_back(root);
            return true;
        }
        bool lhs = findNode(root->left, find, stack);
        if (lhs) {stack.push_back(root); return true;}
        bool rhs = findNode(root->right, find, stack);
        if (rhs) {stack.push_back(root); return true;}
        return false;
    }
public:
    // O(n) time, O(h) space.
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || p == nullptr || q == nullptr) return nullptr;
        
        vector<TreeNode*> pstack, qstack;
        if (!findNode(root, p, pstack)) return nullptr;
        if (!findNode(root, q, qstack)) return nullptr;
        
        TreeNode *node = nullptr;
        while (!pstack.empty() && !qstack.empty() && pstack.back() == qstack.back()) {
            node = pstack.back();
            pstack.pop_back();
            qstack.pop_back();
        }
        return node;
    }
};
