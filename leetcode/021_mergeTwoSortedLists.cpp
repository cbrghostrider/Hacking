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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;
        ListNode *remfrom = l1, *other = l2;                //initial assumption
        if (l1->val > l2->val) { remfrom = l2; other = l1;} //oops, flip choices
        remfrom->next = mergeTwoLists(remfrom->next, other);
        return remfrom;
    }
};
