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
    int halfway = 0;
    int length = 0;
    
    int listLength(ListNode *head) {
        if (head == nullptr) return 0;
        return (1 + listLength(head->next));
    }
    
    //depth denotes where I am currently
    bool isPalindrome(ListNode *head, ListNode*& checkMe, int depth) {
        if (head == nullptr) return true;
        
        if (depth == halfway && (length % 2) == 0) { //even sized list
            checkMe = head->next->next;
            return (head->val == head->next->val);
        } else if (depth == halfway && (length % 2) != 0) { //odd sized list
            checkMe = head->next;
            return true;
        }
        
        bool recVal = isPalindrome(head->next, checkMe, depth+1);
        bool retval = (recVal && head->val == checkMe->val);
        checkMe = checkMe->next;
        return retval;
    }
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr) return true;
        
        length = listLength(head);
        halfway = (length / 2) + (length % 2);
        ListNode *checkMe = 0;
        
        return isPalindrome(head, checkMe, 1);
    }
};
