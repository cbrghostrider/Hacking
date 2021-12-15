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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        
        vector<int> n1s, n2s;
        while (l1) {n1s.push_back(l1->val); l1 = l1->next;}
        while (l2) {n2s.push_back(l2->val); l2 = l2->next;}
        
        vector<int> digits;
        int carry=0;
        while (!n1s.empty() || !n2s.empty()) {
            int d1=0;
            if (!n1s.empty()) {d1=n1s.back(); n1s.pop_back();}
            int d2=0;
            if (!n2s.empty()) {d2=n2s.back(); n2s.pop_back();}
            int sum = d1+d2+carry;
            digits.push_back(sum%10);
            carry=sum/10;
        }
        if (carry) {digits.push_back(carry);}
        
        ListNode* ans=new ListNode(digits.back()); digits.pop_back();
        ListNode *node = ans;
        while (!digits.empty()) {
            ListNode *next = new ListNode(digits.back());
            digits.pop_back();
            node->next = next;
            node = next;
        }
        return ans;
    }
};
