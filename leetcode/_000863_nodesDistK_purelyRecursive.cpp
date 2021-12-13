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
    vector<int> ans;
    
    void pushNodesAtDepth(TreeNode* root, int val) {
        if (root == nullptr) return;
        if (val == 0) {
            ans.push_back(root->val);
            return;
        }
        pushNodesAtDepth(root->left, val-1);
        pushNodesAtDepth(root->right, val-1);
    }
    
    // traverse returns a non-negative non-zero value if target node is found in subtree at root.
    // The value returned is the depth of the target node
    //
    // curr_depth tracks how deep we are within the tree when called, however,
    // it is only updated if it is non-negative.
    // it is initialized to 0 when we encounter the target.
    int traverse(TreeNode* root, TreeNode* target, int k, int curr_depth) {
        if (root == nullptr) return -1;
        
        if (root == target) {
            curr_depth=0;
        }
        if (curr_depth == k) {
            ans.push_back(root->val);
        }
        
        int lhs = traverse(root->left, target, k, curr_depth == -1 ? -1 : curr_depth+1);
        int rhs = traverse(root->right, target, k, curr_depth == -1 ? -1 : curr_depth+1);
        
        if (curr_depth == 0) return 1;
        if (lhs != -1) {
            if (lhs == k) {ans.push_back(root->val);}
            else if (lhs < k) pushNodesAtDepth(root->right, k-lhs-1);
            return lhs+1;
        }
        if (rhs != -1) {
            if (rhs == k) {ans.push_back(root->val);}
            else if (rhs < k) pushNodesAtDepth(root->left, k-rhs-1);
            return rhs+1;
        }
        return -1;
    }
    
public:
    // This solution does a "purely recursive" approach, in that
    // no extra globals (other than ans) are needed.
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        
        if (root == nullptr || target == nullptr || k < 0) return {};
        if (root == target){
            pushNodesAtDepth(root, k);
            return ans;
        }
        traverse(root, target, k, -1);
        return ans;
    }
};
