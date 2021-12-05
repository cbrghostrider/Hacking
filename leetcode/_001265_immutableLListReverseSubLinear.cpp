/**
 * // This is the ImmutableListNode's API interface.
 * // You should not implement it, or speculate about its implementation.
 * class ImmutableListNode {
 * public:
 *    void printValue(); // print the value of the node.
 *    ImmutableListNode* getNext(); // return the next node.
 * };
 */

class Solution {
    
    int getLength(ImmutableListNode *node, ImmutableListNode* stopAt=nullptr) {
        int length = 0;
        while (node != stopAt) {length++; node = node->getNext();}
        return length;
    }
    
public:
    // O(n) time, O(n) space for recursion stack.
    void printLinkedListInReverse_On(ImmutableListNode* head, ImmutableListNode *stopAt=nullptr) {
        if (head == stopAt) return;
        printLinkedListInReverse_On(head->getNext(), stopAt);
        head->printValue();
    }
    
    // O(n^2) time, O(1) space.
    void printLinkedListInReverse_On2(ImmutableListNode* head) {
        int length = getLength(head);
        for (int p=length; p>=1; p--) {
            ImmutableListNode *node = head;
            for (int ctr=1; ctr<p; ctr++) {node = node->getNext();}
            node->printValue();
        }
    }
    
    // Imagine the linkedlist divided up into sqrt(n) chunks.
    // And you store the "head" of each chunk into a vector: (O(sqrt(n))) space.
    // Then for each chunk, you can use the recursive algorithm to print it in (O(sqrt(n))) time and space.
    // for sqrt(n) chunks, total time = sqrt(n)* sqrt(n) = O(n)... 
    // total space = sqrt(n) heads + sqrt(n) for each recursion, which happens sequentially: O(sqrt(n)) total space
    void printLinkedListInReverse(ImmutableListNode* head) {
        const int N = getLength(head);
        const int sqrt_N = static_cast<int>(std::sqrt(static_cast<double>(N)));
        
        vector<ImmutableListNode*> chunks;
        ImmutableListNode *node = head;
        int ctr=0, tgtMult = 0;
        while (node) {
            if (ctr == tgtMult*sqrt_N) {
                chunks.push_back(node);
                tgtMult++;
            }
            node = node->getNext();
            ctr++;
        }
        chunks.push_back(nullptr);
        
        for (int cp=chunks.size()-2; cp>=0; cp--) {
            printLinkedListInReverse_On(chunks[cp], chunks[cp+1]);
        }
    }
};
