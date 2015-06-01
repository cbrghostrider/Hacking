// Using O(n) space currently, need to optimize to O(1) space as per the requirements
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL) return;
        queue<pair<TreeLinkNode*, int>> bfsqueue;
        bfsqueue.push(make_pair(root, 0));
        while (!bfsqueue.empty()) {
            auto me = bfsqueue.front(); bfsqueue.pop();
            if (me.first->left) bfsqueue.push(make_pair(me.first->left, me.second+1));
            if (me.first->right) bfsqueue.push(make_pair(me.first->right, me.second+1));
            if (bfsqueue.empty() || bfsqueue.front().second != me.second) {
                me.first->next = NULL;
                continue;
            }
            me.first->next = bfsqueue.front().first;
        }
    }
};
