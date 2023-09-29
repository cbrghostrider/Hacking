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
    
public:
    
    // Iteratively performed.
    TreeNode* inorderSuccessor_(TreeNode* root, TreeNode* p) {
        if (root == nullptr || p == nullptr) return nullptr;
        
        vector<TreeNode*> stack;
        TreeNode* node = root;
        while (node && node != p) {
            stack.push_back(node);
            if (node->val > p->val) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        
        if (node == nullptr) return nullptr;  // p is not present
        
        if (node->right) {
            node = node->right;
            while (node->left) {node = node->left;}
            return node;
        }
        
        while (!stack.empty() && node == stack.back()->right) {
            node = stack.back();
            stack.pop_back();
        }
        
        if (stack.empty()) return nullptr;
        return stack.back();
    }
};
