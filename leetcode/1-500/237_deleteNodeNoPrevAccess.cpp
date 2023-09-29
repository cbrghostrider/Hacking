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
public:
    void deleteNode(ListNode* node) {
        if (node->next == NULL) return;
        
        while (node->next) {
            node->val = node->next->val;
            if (node->next->next) {
                node = node->next;
            } else {
                break;
            }
        }
        
        ListNode *delMe = node->next;
        node->next = NULL;
        delete delMe;
    }
};
