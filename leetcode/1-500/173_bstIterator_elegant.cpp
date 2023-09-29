// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
    vector<TreeNode*> stack;
    
    void populateStack(TreeNode* root) {
        while (root) {
            stack.push_back(root);
            root = root->left;
        }
    }
public:
    BSTIterator(TreeNode *root) {
        populateStack(root);
    }

    // @return whether we have a next smallest number 
    bool hasNext() {
        return (!stack.empty());
    }

    // @return the next smallest number 
    int next() {
        TreeNode* stackTop = stack.back();
        int retval = stackTop->val;
        stack.pop_back();
        populateStack(stackTop->right);
        return retval;
    }

};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
