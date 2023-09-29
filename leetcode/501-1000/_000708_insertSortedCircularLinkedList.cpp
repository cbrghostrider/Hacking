/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

class Solution {    
    Node* findStart(Node* head) {
        if (head == nullptr || head->next == head) return head;
        Node *start = head, *node = head;
        while (node->next != head) {
            if (node->val > node->next->val) {
                start = node->next;
            }
            node = node->next;
        }
        return start;
    }
    
public:
    Node* insert(Node* head, int insertVal) {                       
        
        if (head == nullptr) {
            Node* node = new Node(insertVal);
            node->next = node;
            return node;
        }
        
        if (head->next == head) {
            Node* node = new Node(insertVal);
            head->next = node;
            node->next = head;
            return head;
        }                
        
        Node* start = findStart(head);
        
        Node* check=start;
        while (check->next != start && check->next->val <= insertVal) {
            check = check->next;
        }
        
        if (check->val > insertVal) {
            Node* last=check;
            while (check->next != last) {                
                check = check->next;
            }
        }     
        Node* node = new Node(insertVal);
        node->next = check->next;
        check->next = node;
        return head;
    }
};
