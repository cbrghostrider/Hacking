/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    ListNode* newHead_;
public:
    ListNode* reverseListPrime(ListNode* head) {
        if (head->next == NULL) {
            newHead_ = head;
            return head;
        }
        
        ListNode* recurseOn = head->next;
        ListNode* me = head; 
        me->next = NULL;
        ListNode *getTail = reverseListPrime(recurseOn);
        getTail->next = me;
        return me;
    }
    
    ListNode* reverseList(ListNode* head) {
        if (head == NULL) return head;
        reverseListPrime(head);
        return newHead_;
    }
};
