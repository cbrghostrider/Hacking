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
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode *grandChild = swapPairs(head->next->next);
        ListNode *child = head->next;
        child->next = head;
        head->next = grandChild;
        return child;
    }
};
