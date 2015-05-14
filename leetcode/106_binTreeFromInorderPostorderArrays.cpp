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
    TreeNode* buildTree_(vector<int>& inorder, int iofrom, int ioto, vector<int>& postorder, int pofrom, int poto) {
        if (inorder.size() == 0 || postorder.size() == 0) return NULL;
        if (iofrom > ioto || pofrom > poto) return NULL; 

        int rootind=0;
        for (int i=iofrom; i<=ioto; i++) {
            if (postorder[poto] == inorder[i]) { //poto points to root in postorder
                rootind = i; break;
            }
        }
        int numlhs = rootind - iofrom; //number of things in left sub tree
        
        TreeNode *root = new TreeNode(postorder[poto]);
        root->left  = buildTree_(inorder, iofrom, rootind-1,  postorder, pofrom, pofrom + numlhs-1);
        root->right = buildTree_(inorder, rootind+1, ioto,    postorder, pofrom + numlhs, poto-1);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return buildTree_(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
    }
};
