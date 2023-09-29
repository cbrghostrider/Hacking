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
    /////////////////////////////////////////////////////////////////////////////
    // O(n) space solution
    // Doesn't make use of the fact that this is a binary "search" tree.
    /////////////////////////////////////////////////////////////////////////////
    std::unordered_map<int, int> kv;
    
    void populate(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        
        if (kv.find(root->val) == kv.end()) {
            kv[root->val] = 1;
        } else {
            kv[root->val] += 1;
        }
        
        populate(root->left);
        populate(root->right);
    }
    
    
    bool find(TreeNode* root, int k) {
        if (root == nullptr) {
            return false;
        }
        
        int other = k - root->val;
        auto iter = kv.find(other);
        if (iter != kv.end()) {
            if (other == root->val && iter->second >= 2) {
                return true;
            } else if (other != root->val) {
                return true;
            }
        }
        
        if (find(root->left, k)) {
            return true;
        }
        return find(root->right, k);
    }
    
    bool findTargetBT(TreeNode* root, int k) {
        populate(root);
        return find(root, k);
    }
    
    /////////////////////////////////////////////////////////////////////////////////
    // For each node in the tree, search the tree to see if (k - node->val) exists.
    // O(n log n) time for balanced BST, O(n^2) time for worst-case BST.
    
    bool search(TreeNode* root, int val) {
        if (root == nullptr) {
            return false;
        }
        if (root->val == val) {
            return true;
        }
        if (root->val > val) {
            return search(root->left, val);
        }
        return search(root->right, val);
    }
    
    int countKBy2 = 0;  // if k is even, counts num of occurrences of k/2.
    
    bool findTgt(TreeNode* orig_root, TreeNode *root, int k) {
        if (root == nullptr) {
            return false;
        }
        
        int other = k - root->val;
        if (other != root->val) {  // if not looking for k/2
            if (search(orig_root, other)) {
                return true;
            }
        } else {
            countKBy2++;
        }
        
        return findTgt(orig_root, root->left, k) || findTgt(orig_root, root->right, k);
    }
    
    bool findTarget(TreeNode* root, int k) {
        return findTgt(root, root, k) || (countKBy2 >= 2);
    }
};
