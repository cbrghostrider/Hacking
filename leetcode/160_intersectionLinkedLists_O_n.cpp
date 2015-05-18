/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    int length(ListNode* h) {
        int len=0;
        while (h) {
            h = h->next;
            len++;
        }
        return len;
    }
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = length(headA);
        int lenB = length(headB);
        if (lenA < lenB) return getIntersectionNode(headB, headA);
        if (lenA == 0 or lenB == 0) return NULL;
        
        //A is longer than B, and therefore, the initial (lenA-lenB) nodes of A cannot be
        //the intersection (else, B would be longer than lenB)
        int ctr=0;
        while (ctr++ < (lenA - lenB)) {
            headA = headA->next;
        }
        
        while (headA && headB && (headA->val != headB->val)) {
            headA = headA->next;
            headB = headB->next;
        }
        return headA;
    }
};
