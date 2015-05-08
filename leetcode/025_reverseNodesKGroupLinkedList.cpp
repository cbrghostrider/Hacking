/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    ListNode* getKthNode_(ListNode* head, int k) {
        while (head && (k-- > 1)) {
            head = head->next;
        }
        return head;
    }

public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *kth = getKthNode_(head, k);
        if (head == NULL || kth == NULL || k == 1) return head;
        
        ListNode *reversedRestHead = reverseKGroup(kth->next, k);
        kth->next = NULL;
        while (head) {
            ListNode *headNext = head->next;
            head->next = reversedRestHead;
            reversedRestHead = head;
            head = headNext;
        }
        return reversedRestHead;
    }
};
