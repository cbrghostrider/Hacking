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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> retval;
        if (root == NULL) return retval;

        deque<pair<TreeNode*, int>> que;
        que.push_back(make_pair(root, 0));
        while (!que.empty()) {
            auto curElem = que.front(); que.pop_front();
            if (curElem.second >= retval.size()) {
                retval.push_back(vector<int>());
            }
            retval[curElem.second].push_back(curElem.first->val);
            if (curElem.first->left) {
                que.push_back(make_pair(curElem.first->left, curElem.second + 1));
            }
            if (curElem.first->right) {
                que.push_back(make_pair(curElem.first->right, curElem.second + 1));
            }
        }
        for (int i=0; i<retval.size(); i++) {
            if (!(i % 2)) continue;
            std::reverse(retval[i].begin(), retval[i].end());
        }
        return retval;
    }
};
