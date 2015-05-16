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
        ListNode* ptr = head;
        while (ptr) {
            ListNode *me = ptr;
            int value = ptr->val;
            ptr = ptr->next;
            while (ptr && ptr->val == value) {
                ListNode* delme = ptr;
                ptr = ptr->next;
                delete delme;
            }
            me->next = ptr;
        }
        return head;
    }
};
