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
    vector<int> pre, post;
    int pre_ptr, post_ptr;
    unordered_set<int> processed;  // the values that are processed

    //
    // Well this was yuck...
    // Need something more elegant. 
    //
    TreeNode* construct(int pre_ptr, int post_ptr) {
        // if (processed.find(pre[pre_ptr]) != processed.end()) return nullptr;
        
        TreeNode* my_root = new TreeNode(pre[pre_ptr]);
        processed.insert(pre[pre_ptr]);
        
        bool left_exists = false, right_exists = false;
        
        int left_pre_ptr = pre_ptr+1;
        int right_post_ptr = post_ptr-1;
        
        if (left_pre_ptr >= pre.size() || right_post_ptr < 0) {
            return my_root;
        }
        if (processed.find(pre[left_pre_ptr]) == processed.end()) {
            left_exists = true;
        }
        if (processed.find(post[right_post_ptr]) == processed.end()) {
            right_exists = true;
        }
        // if both the same value, then only one tree really exists; pick any side
        if (left_exists && right_exists && pre[left_pre_ptr] == post[right_post_ptr]) {
            right_exists = false;
        }
        
        if (left_exists) {
            int left_post_ptr = post_ptr;
            while (left_post_ptr >= 0 && post[left_post_ptr] != pre[left_pre_ptr]) {left_post_ptr--;}
            if (left_post_ptr >=0) my_root->left = construct(left_pre_ptr, left_post_ptr);
        }
        if (right_exists) {
            int right_pre_ptr = pre_ptr;
            while (right_pre_ptr < pre.size() && pre[right_pre_ptr] != post[right_post_ptr]) {right_pre_ptr++;}
            if (right_pre_ptr < pre.size()) my_root->right = construct(right_pre_ptr, right_post_ptr);
        }
        return my_root;
    }
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        pre=preorder;
        post=postorder;
        pre_ptr=0; 
        post_ptr=postorder.size()-1;
        TreeNode* tree = construct(pre_ptr, post_ptr);
        return tree;
    }
};
