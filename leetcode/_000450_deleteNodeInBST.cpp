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
   
    // O(H) time, O(H) space for recursion. 
    // H is the height of the tree.
    TreeNode* deleteIt(TreeNode* root, TreeNode* from, int key) {
        if (root == nullptr) return nullptr;
        if (root->val == key) {
            TreeNode* new_root=nullptr;
            
            // root needs to be deleted.
            if (root->left == nullptr && root->right == nullptr) {
                if (from && from->left == root)  {from->left = nullptr;}
                if (from && from->right == root) {from->right = nullptr;}
                new_root = nullptr;
            } else if (root->right == nullptr) {
                if (from && from->left == root)  {from->left = root->left;}
                if (from && from->right == root) {from->right = root->left;}
                new_root = root->left;
            } else if (root->left == nullptr) {
                if (from && from->left == root)  {from->left = root->right;}
                if (from && from->right == root) {from->right = root->right;}
                new_root = root->right;                
            } else {  // both left and right exist
                TreeNode* node = root->right;
                while (node->left) {
                    node = node->left;
                }
                node->left = root->left;
                if (from && from->left == root)  {from->left = root->right;}
                if (from && from->right == root) {from->right = root->right;}      
                new_root = root->right;
            }           
            
            root->left = root->right = nullptr;
            delete root;
            return new_root;
        }
        
        if (key < root->val) {deleteIt(root->left, root, key);}
        else {deleteIt(root->right, root, key); }
        return root;
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        return deleteIt(root, nullptr, key);
    }
};
