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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (m == 0 || m >= n ) return head;
        ListNode *mprev = NULL, *mnd=NULL, *nnd=NULL, *ptr=head;
        int ctr=1;
        
        //record mprev, m, and n nodes 
        while (ptr) {
            if (ctr == m)  {
                mnd = ptr;
            } else if (ctr == n) {
                nnd = ptr;
                break;
            }
            if (ctr < m) {
                mprev = ptr;
            }
            ptr = ptr->next;
            ctr++;
        }
        
        //able to do conversion only if both m and n nodes exist
        if (mnd && nnd) {
            ListNode* tail = nnd->next;
            nnd->next = NULL;
            ptr = mnd;
            while (ptr) {
                ListNode* nn = ptr->next;
                ptr->next = tail;
                tail = ptr;
                ptr = nn;
            }
        } else {
            return head;
        }
        
        //boundary condition, where m was actually the head node
        if (mprev) {
            mprev->next = nnd;
            return head;
        } else {
            return nnd;
        }
    }
};
