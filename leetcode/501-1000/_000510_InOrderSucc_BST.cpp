/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {
    vector<Node*> stack;
    
    void unroll(Node* node) {
        while (node) {
            stack.push_back(node);
            node = node->left;
        }
    }
    
public:
    Node* inorderSuccessor(Node* node) {
        if (node == nullptr) return nullptr;
        if (node->right) {
            unroll(node->right);
            return stack.back();
        }
        while (node->parent) {
            if (node->parent->left == node) {return node->parent;}
            node = node->parent;
        }
        return nullptr;
    }
};
