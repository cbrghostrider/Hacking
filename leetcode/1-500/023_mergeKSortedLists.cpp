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
    typedef ListNode* VAL;
    typedef int LISTNUM;
    typedef pair<VAL, LISTNUM> HeapVal;
    class HeapCompare {
    public:
        bool operator () (const HeapVal& lhs, const HeapVal& rhs) {
            return (lhs.first->val > rhs.first->val);
        }
    };
    typedef std::priority_queue<HeapVal, std::vector<HeapVal>, HeapCompare> MinHeap;

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        MinHeap heap;
        
        //insert first links of all lists into the minheap
        for (int i=0; i<lists.size(); i++) {
            ListNode *head = lists[i];
            if (head == NULL) continue;
            heap.push(make_pair(head, i)); //value and list that it came from
            lists[i] = head->next;
            head->next = NULL;
        }
        
        ListNode *retval = NULL, *end = NULL;
        //do a k-way merge, using the heap to extract min
        while (!heap.empty()) {
            HeapVal minElem = heap.top(); heap.pop();
            if (retval == NULL) {
                retval = end = minElem.first;
            } else {
                end->next = minElem.first;
                end = minElem.first;
            }
            
            if (lists[minElem.second]) {
                ListNode *newPush = lists[minElem.second];
                heap.push(make_pair(newPush, minElem.second));
                lists[minElem.second] = newPush->next;
                newPush->next = NULL;
            }
        }
        
        return retval;
    }
};
