/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    unordered_map<ListNode*, bool> nodeMap_;
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL) return false;
        ListNode *ptr=head;
        while (ptr) {
            nodeMap_.insert(make_pair(ptr, true));
            if (nodeMap_.find(ptr->next) != nodeMap_.end()) return ptr->next;
            ptr = ptr->next;
        }
        return NULL;
    }
};
