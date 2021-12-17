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
    int len=0;
    ListNode* head=nullptr;
public:
    Solution(ListNode* h) : head(h) { 
        len = 0;
        ListNode *node = head;
        while (node) {
            len++;
            node = node->next;
        }
    }
    
    int getRandom() {
        if (len == 0) return -1;
        if (len == 1) return head->val;
        
        int r = std::rand() % len; 
        ListNode* node = head;
        while (r != 0) {
            node = node->next;
            r--;
        }
        return node->val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
