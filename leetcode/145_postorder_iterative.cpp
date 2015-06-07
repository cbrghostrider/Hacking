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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> retval;
        vector<pair<TreeNode*, bool>> myStack;
        
        //bool indicates whether I am in one of two phases
        //1. bool == true phase:  I push (root, false), (right, true), (left, true) onto myStack
        //2. bool == false phase: I push my value on retval, and pop myself
        myStack.push_back(make_pair(root, true));
        while (!myStack.empty()) {
            auto inspect = myStack.back(); myStack.pop_back();
            TreeNode* me = inspect.first;
            if (me == NULL) continue;
            if (inspect.second == true) {
                myStack.push_back(make_pair(me, false));
                myStack.push_back(make_pair(me->right, true));
                myStack.push_back(make_pair(me->left, true));
            } else {
                retval.push_back(me->val);
            }
        }
        return retval;
    }
};
