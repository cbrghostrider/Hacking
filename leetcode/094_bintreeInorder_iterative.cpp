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
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> retval;
        if (root == NULL) return retval;
        vector<pair<TreeNode*,bool>> stack;
        stack.push_back(make_pair(root, true));
        while (!stack.empty()) {
            auto me = stack.back(); stack.pop_back();
            if (me.second == false){
                retval.push_back(me.first->val);
                continue;
            }
            if (me.first->right) {
                stack.push_back(make_pair(me.first->right, true));
            }
            stack.push_back(make_pair(me.first, false));
            if (me.first->left) {
                stack.push_back(make_pair(me.first->left, true));
            }
        }
        return retval;
    }
};
