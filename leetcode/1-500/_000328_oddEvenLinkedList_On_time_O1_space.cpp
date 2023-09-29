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
    // O(n) time, O(1) space.
    ListNode* oddEvenList(ListNode* head) {
        ListNode* ret = head;
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) return ret;
        
        ListNode *odd_end, *odd;
        ListNode *even_start, *even;
        odd_end = odd = head;
        even_start = even = head->next;
        
        while (odd) {
            ListNode *next_odd=nullptr, *next_even=nullptr;
            if (even) {next_odd = even->next;} 
            if (even && even->next) {next_even = even->next->next;}
            if (odd) {odd->next = next_odd;}
            if (even) {even->next = next_even;}
            odd_end = odd;
            odd = next_odd;
            even = next_even;
        }
        odd_end->next = even_start;
        return ret;
    }
};
