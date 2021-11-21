/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteNodes(ListNode* head, int m, int n) {
        if (head == nullptr || m <= 0 || n <= 0) return head;
        if (head->next == nullptr) {return head;}
        
        ListNode *prev = nullptr, *node = head;
        
        while (node) {
            int m_rem = m;
            while (node && m_rem) {
                prev = node;
                node = node->next;
                m_rem--;
            }
            if (node == nullptr) return head;
            
            int n_rem = n;
            while (node && n_rem) {
                ListNode* rem = node;
                node = node->next;
                n_rem--;
                delete rem;
            }
            prev->next = node;
        }
        return head;        
    }
};
