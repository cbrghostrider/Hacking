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
    void getParents(Node* n, unordered_set<Node*>& parents) {
        if (n == nullptr) return;
        parents.insert(n);
        getParents(n->parent, parents);
    }
    
    int getHeight(Node* n) {
        int height = 0;
        while (n != nullptr) {
            height++;
            n = n->parent;
        }
        return height;
    }
public:
    // O(h) time, O(h) space.
    Node* lowestCommonAncestor_oh_oh(Node* p, Node * q) {
        unordered_set<Node*> pp; 
        getParents(p, pp);
        Node *n = q;
        while (pp.find(n) == pp.end()) {
            n = n->parent;
        }
        return n;
    }
    
    // O(h) time, O(1) space.
    Node* lowestCommonAncestor(Node* p, Node * q) {
        int hp = getHeight(p), hq = getHeight(q);
        while (hp < hq) {
            q = q->parent; hq--;
        }
        while (hp > hq) {
            p = p->parent; hp--;
        }
        while (p != q) {p = p->parent; q = q->parent;}
        return p;
    }
};
