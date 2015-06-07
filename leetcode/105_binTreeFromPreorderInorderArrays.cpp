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
private:
    TreeNode* buildTree_( vector<int>& preorder, int pofrom, int poto, vector<int>& inorder, int iofrom, int ioto) {
        if (inorder.size() == 0 || preorder.size() == 0) return NULL;
        if (iofrom > ioto || pofrom > poto) return NULL; 

        int rootind=0;
        for (int i=iofrom; i<=ioto; i++) {
            if (preorder[pofrom] == inorder[i]) { //pofrom points to root in preorder
                rootind = i; break;
            }
        }
        int numlhs = rootind - iofrom; //number of things in left sub tree
        
        TreeNode *root = new TreeNode(preorder[pofrom]);
        root->left  = buildTree_(preorder, pofrom+1, pofrom + 1 + numlhs-1, inorder, iofrom, rootind-1);
        root->right = buildTree_(preorder, pofrom + 1 + numlhs, poto,       inorder, rootind+1, ioto);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return (buildTree_(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1));
    }
};
