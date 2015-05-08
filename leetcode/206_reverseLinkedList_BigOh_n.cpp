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
    ListNode* reverseList(ListNode* head) {
        ListNode* reversedRestHead = NULL;
        while (head) {
            ListNode *headNext = head->next;
            head->next = reversedRestHead;
            reversedRestHead = head;
            head = headNext;
        }
        return reversedRestHead;
    }
};
