// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */

//iterative solution takes extra space (for queue)

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL) return;
        root->next = 0; //clobbering next pointer to store level temporarily
        
        deque<TreeLinkNode*> que;
        que.push_back(root);
        TreeLinkNode *me = NULL;
        
        while (!que.empty()) {
            me = que.front(); que.pop_front();
            if (me->left) {
                me->left->next = me->next+1;
                que.push_back(me->left);
            }
            if (me->right) {
                me->right->next = me->next+1;
                que.push_back(me->right);
            }
            if (que.empty() || que.front()->next != me->next) {
                me->next = NULL;
            } else {
                me->next = que.front();
            }
        }
    }
};
