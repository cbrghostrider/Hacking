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
    ListNode* lastButOne_(ListNode* head) {
        while (head->next->next != NULL) {
            head = head->next;
        }
        return head;
    }
    void reorderList(ListNode* head) {
        if (head == NULL || head->next == NULL || head->next->next == NULL) return;
        
        ListNode* moveAfter = head;
        while (1) {
            ListNode* lastButOne = lastButOne_(head);
            ListNode* moveMe = lastButOne->next;
            if (moveAfter == lastButOne || moveAfter == moveMe) break;
            lastButOne->next = NULL;            //new last node
            moveMe->next = moveAfter->next;
            moveAfter->next = moveMe;
            moveAfter = moveAfter->next->next;
        }
    }
};
