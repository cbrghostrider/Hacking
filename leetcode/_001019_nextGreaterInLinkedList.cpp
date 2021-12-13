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
    // Using a monotonic stack.
    // O(n) space, O(n) time.
    vector<int> nextLargerNodes(ListNode* head) {
        vector<ListNode*> stack;
        vector<int> ans, ng;
        
        while (head) {
            stack.push_back(head);
            head = head->next;
        }
        
        while (!stack.empty()) {
            while (!ng.empty() && ng.back() <= stack.back()->val) {ng.pop_back();} 
            ans.push_back(ng.empty() ? 0 : ng.back());
            ng.push_back(stack.back()->val);
            stack.pop_back();
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
