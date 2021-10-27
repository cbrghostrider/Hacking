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
    // inserts existing BST "subtree" with no left side, into existing BST "root"
    // note that the smallest value in subtree is larger than the largest value in root tree.
    void insertSubtree(TreeNode *root, TreeNode *subtree) {
        while (root->right != nullptr) {
            root = root->right;
        }
        root->right = subtree;
    }
    
    TreeNode* pushRightCurrent(TreeNode *root) {
        while (root->left != nullptr) {
            TreeNode *newTree = root->left;
            root->left = nullptr;
            insertSubtree(newTree, root);
            root = newTree;
        }
        return root;
    }
    
    TreeNode *tree = nullptr;
    
    TreeNode* increasingBST(TreeNode* root) {
        tree = pushRightCurrent(root);
        TreeNode *curr = tree;
        while (curr->right) {
            TreeNode *node = pushRightCurrent(curr->right);
            curr->right = node;
            curr = node;
        }
        return tree;
    }
};
