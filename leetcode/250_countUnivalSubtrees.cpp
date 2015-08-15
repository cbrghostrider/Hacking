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
    
    // return value says: Am I as a whole a unival subtree
    // retCount indicates how many trees underneath and including me are unival
    bool isUnivalTree_(TreeNode* root, int& retCount) {
        if (root == NULL) { retCount = 0; return true;}   //trivially unival
        
        if (root->left == NULL && root->right == NULL) {  //I am unival subtree
            retCount = 1; 
            return true;
        } 
        
        int lhsret=0, rhsret=0;
        bool lhsUnival = isUnivalTree_(root->left, lhsret);
        bool rhsUnival = isUnivalTree_(root->right, rhsret);
        retCount += lhsret; //will be returned regardless of my status
        retCount += rhsret; //will be returned regardless of my status
        
        bool iAmUnival = (lhsUnival && ((root->left==NULL) || root->left->val == root->val))
                       && (rhsUnival && ((root->right==NULL) || root->right->val == root->val));
        retCount += (iAmUnival ? 1 : 0);
        return iAmUnival;
    }
    
    int countUnivalSubtrees(TreeNode* root) {
        int retval = 0;
        isUnivalTree_(root, retval);
        return retval;
    }
};
