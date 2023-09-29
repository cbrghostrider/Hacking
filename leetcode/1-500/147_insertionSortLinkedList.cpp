// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
 //will maintain the invariant that everything to the right of sorted_ pointer is sorted
 //at the conclusion of the algorithm, sorted_ is the sorted linked list
class Solution {
private:
    ListNode* sorted_;
    
    //inserts a node in a sorted list
    void insertInSorted_(ListNode* node) {
        if (sorted_ == NULL || node->val < sorted_->val) {
            node->next = sorted_;
            sorted_ = node;
            return;
        }
        ListNode* ptr = sorted_;
        while (ptr->next && (node->val > ptr->next->val)) {
            ptr = ptr->next;
        }
        node->next = ptr->next;
        ptr->next = node;
    }
public:
    ListNode* insertionSortList(ListNode* head) {
        sorted_ = NULL;
        while (head) {
            ListNode* me = head;
            head = head->next;
            me->next = NULL;
            insertInSorted_(me);
        }
        return sorted_;
    }
};
