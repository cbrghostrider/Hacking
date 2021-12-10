/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
    struct Info {
        Node *min=nullptr;
        Node *max=nullptr;
    };
    
    Info traverse(Node* root) {
        if (root == nullptr) return {nullptr, nullptr};
        Info lhs = traverse(root->left);
        Info rhs = traverse(root->right);
        if (root->left) {
            lhs.max->right = root;
            root->left = lhs.max;
        }
        if (root->right) {
            rhs.min->left = root;
            root->right = rhs.min;
        }
        return {lhs.min ? lhs.min : root,
                rhs.max ? rhs.max : root};
    }
    
public:
    Node* treeToDoublyList(Node* root) {
        Info info = traverse(root);
        if (root) {  // make it circular
            info.min->left = info.max;
            info.max->right = info.min;
        }
        return info.min;
    }
};
