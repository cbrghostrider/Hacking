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
        int ctr=0;
        while (h) {
            h = h->next; 
            ctr++;
        }
        return ctr;
    }
public:
    ListNode* rotateRight(ListNode* head, int k) {
        int len = length(head);
        if (len == 0 || (k % len)<=0) return head;
        k = k % len;   // to guard against multiple rotations
        int rot = len - k;
        
        ListNode *newhead = NULL, *end = head, *ptr = head->next;
        while (ptr && (rot-- > 1)) {
            end = ptr;
            ptr = ptr->next;
        }
        end->next = NULL;
        if (ptr) {
            newhead = ptr;
            while (ptr->next) {
                ptr = ptr->next;
            }
            ptr->next = head;
        } else {
            newhead = head;
        }
        return newhead;
    }
};
