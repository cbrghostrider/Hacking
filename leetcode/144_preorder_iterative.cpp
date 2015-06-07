// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> retval;
        vector<TreeNode*> myStack; //keep track of the nodes
        myStack.push_back(root);
        while (!myStack.empty()) {
            TreeNode* me = myStack.back();
            myStack.pop_back();
            if (me == NULL) continue;
            retval.push_back(me->val);
            myStack.push_back(me->right);
            myStack.push_back(me->left);
        }
        return retval;
    }
};
