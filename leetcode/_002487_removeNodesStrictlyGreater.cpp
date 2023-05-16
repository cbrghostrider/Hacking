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
    ListNode* removeNodes(ListNode* head) {
        if (head == nullptr) return head;
        vector<ListNode*> stack;
        ListNode *node = head;
        while (node) {
            stack.push_back(node);
            node = node->next;
        }

        ListNode *check = stack.back();        
        for (int i=stack.size()-2; i>=0; i--) {
            ListNode *node = stack[i];
            if (check->val > node->val) {
                // Remove node.
                if (i != 0) {
                    stack[i-1]->next = check;
                }
            } else {
                check = node;
            }            
        }
        return check;
    }
};
