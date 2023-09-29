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
    // Records info for a given subtree rooted at "root".
    struct Info {
        int num_paths;     // number of paths leading up to targetSum in this subtree
        vector<int> sums;  // sums of all paths ending in root 
    };
    
    Info traverse(TreeNode* root, int target) {
        if (root == nullptr) {return {0, {}};}
        
        Info lhs = traverse(root->left,  target);
        Info rhs = traverse(root->right, target);
        
        Info ret;
        ret.num_paths = lhs.num_paths + rhs.num_paths;
        for (int n : lhs.sums) {
            int psum = n + root->val;
            ret.sums.push_back(psum);
            if (psum == target) {ret.num_paths++;}
        }
        for (int n : rhs.sums) {
            int psum = n + root->val;
            ret.sums.push_back(psum);
            if (psum == target) {ret.num_paths++;}
        }
        ret.sums.push_back(root->val);
        if (root->val == target) {ret.num_paths++;}
        return ret;
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        Info info = traverse(root, targetSum);
        return info.num_paths;
    }
};
