// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    unordered_set<ListNode*> nodeSet_;
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL) return false;
        ListNode *ptr=head;
        while (ptr) {
            nodeSet_.insert(ptr);
            if (nodeSet_.find(ptr->next) != nodeSet_.end()) return ptr->next;
            ptr = ptr->next;
        }
        return NULL;
    }
};
