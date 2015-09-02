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

typedef pair<double, int> Cand;
struct CandCmp {
    bool operator () (const Cand& lhs, const Cand& rhs) {
        return (lhs.first > rhs.first);
    }
};

typedef priority_queue<Cand, vector<Cand>, CandCmp> MinHeap;

class Solution {
    MinHeap mheap;
    double absDiff(int val, double target) {
        return (fabs(((double)val) - target));
    }
    
    void dfs(TreeNode* root, double target) {
        if (root == NULL) return;
        double mydiff = absDiff(root->val, target);
        mheap.push(make_pair(mydiff, root->val));
        dfs(root->left, target);
        dfs(root->right, target);
    }
    
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        dfs(root, target);
        vector<int> retval;
        while (!mheap.empty() && retval.size() < k) {
            Cand cand = mheap.top(); mheap.pop();
            retval.push_back(cand.second);
        }
        return retval;
    }
};

