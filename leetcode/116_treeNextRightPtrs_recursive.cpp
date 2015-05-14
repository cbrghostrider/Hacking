/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

//Recursive solution takes no extra space
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
    //connect rhs nodes for LHS subtree with lhs nodes of RHS subtree
    void connectLSTrhsRSTlhs(TreeLinkNode *lhs, TreeLinkNode *rhs) {
        while (lhs && rhs) {
            lhs->next = rhs;
            lhs = lhs->right; 
            rhs = rhs->left;
        }
    }
    
    //set rhs of right sub tree to NULL
    void nullifyRSTrhs(TreeLinkNode* rhs) {
        while (rhs) {
            rhs->next = NULL;
            rhs = rhs->right;
        }
    }
    
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL) return;
        connect(root->left);
        connect(root->right);
        connectLSTrhsRSTlhs(root->left, root->right);
        nullifyRSTrhs(root->right);
    }
};
