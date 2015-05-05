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
    bool hasCycle(ListNode *head) {
        if (head == NULL || head->next == NULL) return false;
        ListNode *slow = head;
        ListNode* fast = head->next;
        while (fast->next && fast->next->next) {
            if (fast->next == slow) return true;
            fast = fast->next->next;
            slow = slow->next;
        }
        return false;
    }
};
