/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
    
    // flattens head recursively, and returns the start and end of the resulting linked list
    pair<Node*, Node*> flattenInternal(Node* head) {
        if (head == nullptr) return {nullptr, nullptr};
        Node *start=head, *end = head;
        while (head) {
            Node* next = head->next;
            if (next) { end = next; }
            
            if (head->child != nullptr) {
                auto sublist = flattenInternal(head->child);
                
                head->next = sublist.first;
                sublist.first->prev = head;
                
                if (next) {next->prev = sublist.second;}
                sublist.second->next = next;
                
                if (next) { end = next; } else {end = sublist.second;}
                head->child = nullptr;
            } 
            head = next;
        }
        return make_pair(start, end);
    }
public:
    Node* flatten(Node* head) {
        auto f = flattenInternal(head);
        return f.first;
    }
};
