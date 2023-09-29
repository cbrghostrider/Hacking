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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    TreeNode* sortedListToBST_(ListNode* head, int len) {
        if (head == 0 || len <= 0) return NULL;
        int mid = len/2;
        int ctr=0;
        ListNode* lst = head;
        while (ctr++ < mid) {
            lst = lst->next;
        }
        TreeNode* root = new TreeNode(lst->val);
        root->left  = sortedListToBST_(head, mid);
        root->right = sortedListToBST_(lst->next, len-(mid+1));
        return root;
    }
public:
    TreeNode* sortedListToBST(ListNode* head) {
        int len=0;
        ListNode *ptr = head;
        while (ptr) {
            len++;
            ptr = ptr->next;
        }
        return (sortedListToBST_(head, len));
    }
};
