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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len=0;
        ListNode *ptr = head;
        while (ptr) {
            len++;
            ptr = ptr->next;
        }
        if (n <= 0 || n > len) return head;
        if (n == len) {
            ptr = head->next;
            delete head;
            return ptr;
        }
        int ctr=1;
        ptr = head;
        while (ptr && ctr++ < (len - n)) {
            ptr = ptr->next;
        }
        ListNode* delme = ptr->next;
        ptr->next = ptr->next->next;
        delete delme;
        return head;
    }
};
