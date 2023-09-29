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
    ListNode* removeElements(ListNode* head, int val) {
        if (head == NULL) return head;
        while (head && head->val == val) {
            ListNode* delme = head;
            head = head->next;
            delete delme;
        }
        ListNode* prev = head;
        while (prev && prev->next) {
            if (prev->next->val == val) {
                ListNode* delme = prev->next;
                prev->next = prev->next->next;
                delete delme;
            } else {
                prev = prev->next;
            }
        }
        return head;
    }
};
