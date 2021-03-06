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
    void placeNode(ListNode* ptr, ListNode*& h, ListNode*& t) {
        if (h == NULL) h = ptr;
        if (t == NULL) t = ptr;
        else {
            t->next = ptr;
            t = ptr;
        }
    }
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *lthead=NULL, *lttail=NULL;
        ListNode *gthead=NULL, *gttail=NULL;
        ListNode* ptr = head;
        while (ptr) {
            ListNode* pnext = ptr->next;
            ptr->next = NULL;
            if (ptr->val < x) {
                placeNode(ptr, lthead, lttail);
            } else {
                placeNode(ptr, gthead, gttail);
            }
            ptr = pnext;
        }
        if (lttail) lttail->next = gthead;
        if (lthead) return lthead; else return gthead;
    }
};
