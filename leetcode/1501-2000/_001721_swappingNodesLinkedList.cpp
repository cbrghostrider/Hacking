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
    int lenList(ListNode* node) {
        if (node == nullptr) return 0;
        int len=0;
        while (node) {
            len++;
            node = node->next;
        }
        return len;
    }
    
    ListNode* getPred(ListNode* head, int pos) {
        if (head == nullptr || pos == 1) {
            return nullptr;
        }
        
        ListNode* pred = head;
        ListNode* node = head->next;
        pos--;
        
        while (node && pos != 1) {
            pred = node;
            node = node->next;
            pos--;
        }
        return pred;
    }
    
    ListNode* swapSelf(ListNode* head) {
        return head;
    }
    
    // early won't be first node
    ListNode* swapAdjacent(ListNode* head, int early) {
        ListNode* pred = getPred(head, early);
        
        ListNode* n1 = pred->next;
        ListNode* n2 = pred->next->next;
        
        n1->next = n2->next;
        n2->next = n1;
        pred->next = n2;
        
        return head;
    }
    
    // list is at least length 2
    ListNode* swapEnds(ListNode* head, int len) {
        ListNode* pred_end = getPred(head, len);
        
        if (pred_end == head) {
            ListNode* n2 = pred_end->next;
            n2->next = head;
            head->next = nullptr;
            return n2;
        }
        
        ListNode* n1 = head;
        ListNode* n2 = pred_end->next;
        
        n2->next = n1->next;
        n1->next = nullptr;
        pred_end->next = n1;
        
        return n2;
    }
    
    ListNode* swapVanilla(ListNode* head, int p1, int p2) {
        ListNode* n1_pred = getPred(head, p1);
        ListNode* n2_pred = getPred(head, p2);
        ListNode* n1 = n1_pred->next;
        ListNode* n2 = n2_pred->next;
        
        n1_pred->next = n2;
        n2_pred->next = n1;
        ListNode* temp = n2->next;
        n2->next = n1->next;
        n1->next = temp;
        
        return head;
    }
    
public:
    ListNode* swapNodes(ListNode* head, int k) {        
        int len = lenList(head);
        
        // nothing to swap
        if (head == nullptr || k > len) return head;
        
        int pos1 = k, pos2 = len-k+1;
        
        if (pos1 > pos2) {
            std::swap(pos1, pos2);
        }

        if (pos1 == pos2) {
            return swapSelf(head);            
        }
        
        if (pos1 == 1) {
            return swapEnds(head, len);
        }
        
        if (pos1 + 1 == pos2) {
            return swapAdjacent(head, pos1);
        }        
        
        return swapVanilla(head, pos1, pos2);
    }
};
