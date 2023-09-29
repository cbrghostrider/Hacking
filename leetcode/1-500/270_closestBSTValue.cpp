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
    int closest;
    double mindiff;
    double absDiff(int val, double target) {
        return (fabs(((double)val) - target));
    }
    void dfs(TreeNode* root, double target) {
        if (root == NULL) return;
        double myabsdiff = absDiff(root->val, target);
        if (myabsdiff < mindiff) {
            mindiff = myabsdiff;
            closest = root->val;
        }
        dfs(root->left, target);
        dfs(root->right, target);
    }
public:
    int closestValue(TreeNode* root, double target) {
        if (root == NULL) return 0;
        closest = root->val;
        mindiff = absDiff(closest, target);
        dfs(root, target);
        return closest;
    }
};
