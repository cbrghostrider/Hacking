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
    bool areCopies(TreeNode* tree1, TreeNode* tree2) {
        if (tree1 == nullptr || tree2 == nullptr) {
            if (tree1 == nullptr && tree2 == nullptr) {
                return true;
            }
            return false;
        }
        if (tree1->val != tree2->val) {
            return false;
        }
        if (!areCopies(tree1->left, tree2->left)) {
            return false;
        }
        if (!areCopies(tree1->right, tree2->right)) {
            return false;
        }
        return true;
    }
    
    bool preOrder(TreeNode* root, TreeNode* subRoot) {
        if (areCopies(root, subRoot)) {
            return true;
        }
        if (root == nullptr) {
            return false;
        }
        if (root->left && preOrder(root->left, subRoot)) {
            return true;
        }
        return (root->right ? preOrder(root->right, subRoot) : false);
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (subRoot == nullptr) {
            return true;
        }
        return preOrder(root, subRoot);
    }
};
