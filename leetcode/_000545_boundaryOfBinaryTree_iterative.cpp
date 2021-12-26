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
    vector<int> lb, rb, leaves;
    TreeNode* root = nullptr;
    
    bool isLeaf(TreeNode* node) {
        if (node == nullptr) return false;
        return node->left == nullptr && node->right == nullptr;
    }    
    void populateLB(TreeNode* node) {        
        if (node == nullptr) return;
        while (node->left) {
            if (isLeaf(node->left)) break;
            lb.push_back(node->left->val);            
            node = node->left;
        }        
        if (node != root && node->left == nullptr && node->right) {
            if (!isLeaf(node->right)) {
                lb.push_back(node->right->val);
                populateLB(node->right);
            }
        }        
    }
    void populateRB(TreeNode* node) {
        if (node == nullptr) return;
        while (node->right) {
            if (isLeaf(node->right)) break;
            rb.push_back(node->right->val);            
            node = node->right;
        }        
        if (node != root && node->right == nullptr && node->left) {
            if (!isLeaf(node->left)) {
                rb.push_back(node->left->val);
                populateRB(node->left);
            }
        }        
    }
    void populateLeaves(TreeNode* node) {
        if (node == nullptr) return;
        if (isLeaf(node)) {
            if (node != root) leaves.push_back(node->val);
            return;
        }
        populateLeaves(node->left);
        populateLeaves(node->right);
    }
public:
    // O(n) time to visit all the nodes.
    // O(h) space for recursion.
    vector<int> boundaryOfBinaryTree(TreeNode* rootptr) {
        if (rootptr == nullptr) return {};
        root = rootptr;
        vector<int> ans(1, root->val);

        populateLB(root);        
        ans.insert(ans.end(), lb.begin(), lb.end());

        populateLeaves(root);        
        ans.insert(ans.end(), leaves.begin(), leaves.end());

        populateRB(root);
        ans.insert(ans.end(), rb.rbegin(), rb.rend());
        return ans;
    }
};
