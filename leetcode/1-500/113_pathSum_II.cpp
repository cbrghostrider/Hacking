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
    vector<vector<int>> pathSum_(TreeNode* root, int sum) {
        vector<vector<int> > retval;
        if (root == NULL) return retval;
        if (root->left == NULL && root->right == NULL) {
            if (sum == root->val) {
                vector<int> ret(1, sum);
                retval.push_back(ret);
            }
            return retval;    
        }
        
        sum -= root->val;
        vector<vector<int>> vv1 = pathSum_(root->left, sum);
        vector<vector<int>> vv2 = pathSum_(root->right, sum);
        if (retval.empty()) retval = vv1; else retval.insert(retval.end(), vv1.begin(), vv1.end());
        if (retval.empty()) retval = vv2; else retval.insert(retval.end(), vv2.begin(), vv2.end());
        for (vector<int>& vec : retval) {
            vec.push_back(root->val);
        }
        return retval;
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int> > retval = pathSum_(root, sum);
        for_each(retval.begin(), retval.end(), [] (vector<int>& vec) -> void {
            std::reverse(vec.begin(), vec.end());
        });
        return retval;
    }
};
