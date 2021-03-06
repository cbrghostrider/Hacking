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
 
 
class Solution {
private:
    vector<ListNode*> stack_; 
    
    //even though reorderList changes this order, we use only the latter half,
    //*before* reorder messes with that part
    void prepareStack_(ListNode* head) {
        while (head) {
            stack_.push_back(head);
            head = head->next;
        }
    }
    
public:
    void reorderList(ListNode* head) {
        if (head == NULL || head->next == NULL || head->next->next == NULL) return;
        
        prepareStack_(head);
        
        ListNode* moveAfter = head;
        while (1) {
            ListNode* moveMe = stack_.back(); 
            stack_.pop_back();
            ListNode* lastButOne = stack_.back();
            lastButOne->next = NULL;            //new last node
            moveMe->next = moveAfter->next;
            moveAfter->next = moveMe;
            moveAfter = moveAfter->next->next;
            if (moveAfter == lastButOne || moveAfter->next == lastButOne) break;
        }
    }
};
