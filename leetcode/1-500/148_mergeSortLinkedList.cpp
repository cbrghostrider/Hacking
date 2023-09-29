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
   int lenList_(ListNode* ptr) {
        int length = 0;
        while (ptr) {
            length++;
            ptr = ptr->next;
        }
        return length;
   }
   
   //merging two sorted lists
   ListNode* mergeSortedLists_(ListNode* lhs, ListNode* rhs) {
       if (lhs == NULL) return rhs;
       if (rhs == NULL) return lhs;
       bool isLhsMin = (lhs->val < rhs->val);
       ListNode* min    = isLhsMin ? lhs : rhs;
       ListNode* newlhs = isLhsMin ? lhs->next : lhs;
       ListNode* newrhs = isLhsMin ? rhs : rhs->next;
       min->next = mergeSortedLists_(newlhs, newrhs);;
       return min;
   }
   
   //breaks a list into two halves
   void divideList_(ListNode* head, int length, ListNode*& lhs, ListNode*& rhs) {
       lhs = head;
       ListNode* ptr = head;
       int ctr=0;
       while (ctr++ < ((length/2) - 1)) {
           ptr = ptr->next; 
       }
       rhs = ptr->next;
       ptr->next = NULL; //to set LHS end point
   }
   
public:
    ListNode* sortList(ListNode* head) {
        int length = lenList_(head);
        if (length == 0 || length == 1) {
            return head;
        }
        ListNode* lhs=NULL; ListNode* rhs=NULL;
        divideList_(head, length, lhs, rhs);
        return mergeSortedLists_(sortList(lhs), sortList(rhs));
    }
};
