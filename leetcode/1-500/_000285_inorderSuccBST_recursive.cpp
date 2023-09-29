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
    // If I have a right child, just return the leftmost leaf on that side.        
    // If I don't have a right child, 
    // keep climbing back up the tree as long as I am the right child of my parent
    // the moment I'm the left child of my parent, output that parent
    // if there's no such parent, then I'm the mightiest, so return nullptr
    
    TreeNode* leftmost(TreeNode* node) {
        if (node->left) return leftmost(node->left);
        return node;
    }
    
    pair<bool, TreeNode*> succ(TreeNode* root, TreeNode* p, TreeNode* from) {
        if (root == nullptr || p == nullptr) return {true, nullptr};
        
        if (root != p) {
            if (root->val > p->val) {
                return succ(root->left, p, root);
            }
            
            // Only going to the right can potentially return a failure
            auto rhs = succ(root->right, p, root);
            if (rhs.first == true) return rhs;
            if (from && from->left == root) return {true, from};
            return {false, nullptr};
        }
        
        // root == p
        if (root->right) {
            TreeNode* node = leftmost(root->right);
            return {true, node};
        }
        if (from && from->left == root) {
            return {true, from};
        }
        return {false, nullptr};   // I can't provide the answer, look back on recursion stack.
    }
    
public:
    // Recursively performed.
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        auto result = succ(root, p, nullptr);
        return result.second;
    }
 };
