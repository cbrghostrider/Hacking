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
    
    int lengthTree(TreeNode* root) {
        if (root == 0) {
            return 0;
        }
        
        int maxLenRight = lengthTree(root->right);
        int maxLenLeft  = lengthTree(root->left);
        
        return (1 + (maxLenRight > maxLenLeft ? maxLenRight : maxLenLeft));
    }
    
    vector<int> leftSideRHSView(TreeNode* root, int n) {
        vector<int> retval;
        if (root == NULL) {
            return retval;
        }
        if (n == 0) {
            return rightSideView(root);
        }
        
        int lhslen = lengthTree(root->left);
        int rhslen = lengthTree(root->right);
        vector<int> lhs, rhs;
        
        if (rhslen >= n) {
            rhs = leftSideRHSView(root->right, n-1);
        }
        if (lhslen >= n && lhslen > rhslen) {
            int cand1 = n-1;
            int cand2 = rhslen;
            lhs = leftSideRHSView(root->left, cand1 > cand2 ? cand1: cand2);
        }
        
        //do NOT add my current root->val
        if (rhs.size() > 0) retval.insert(retval.end(), rhs.begin(), rhs.end());
        if (lhs.size() > 0) retval.insert(retval.end(), lhs.begin(), lhs.end());
        return retval;
    }

    vector<int> rightSideView(TreeNode* root) {
        vector<int> retval;
        if (root == 0) {
            return retval;
        }
        
        vector<int> rhs, lhs;
        rhs = rightSideView(root->right);
        
        if (lengthTree(root->right) < lengthTree(root->left)) { //lhs is deeper than rhs
            lhs = leftSideRHSView(root->left, lengthTree(root->right));
        }
        
        retval.push_back(root->val);
        if (rhs.size() > 0) retval.insert(retval.end(), rhs.begin(), rhs.end());
        if (lhs.size() > 0) retval.insert(retval.end(), lhs.begin(), lhs.end());
        return retval;
    }
    
};
