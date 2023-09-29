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
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode* ptrprev = head, *ptr = head->next;
        int value = head->val;
        while (ptr && ptr->val == value) {
            ptrprev = ptr;
            ptr = ptr->next;
        }
        ListNode* rest = deleteDuplicates(ptr);
        if (ptrprev == head) { //no duplicates in this part
            head->next = rest;
            return head;
        }
        ptrprev->next = NULL;
        while (head) {
            ListNode* nextn = head->next;
            delete head;
            head = nextn;
        }
        return rest;
    }
};


