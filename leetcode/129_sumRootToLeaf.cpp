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
    vector<int> stack_;
    int sum = 0;

    int convertNumber_() {
        //strip leading zeroes
        auto startit = std::find_if_not(stack_.begin(), stack_.end(), [] (const int& n) -> bool {return (n == 0);});
        
        int localSum=0;
        for (auto it=startit; it != stack_.end(); it++) {
            localSum = localSum*10 + (*it);
        }
        return localSum;
    }
    
    void dfs_(TreeNode *root) {
        if (root == NULL) {
            sum += convertNumber_();
            return;
        }
        
        stack_.push_back(root->val);
        if (root->left) dfs_(root->left);
        if (root->right) dfs_(root->right);
        if (root->left == NULL && root->right == NULL) dfs_(NULL);
        stack_.pop_back();
    }

public:        
    
    int sumNumbers(TreeNode* root) {
        dfs_(root);
        return sum;
    }
};
