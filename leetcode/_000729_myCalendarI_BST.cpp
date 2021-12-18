class MyCalendar {
    struct Node {
        int start=0;  // inclusive
        int end=0;    // not inclusive
        Node* left =nullptr;
        Node* right=nullptr;
    };
    Node *root = nullptr;
    
    // will never be called with overlapping interval
    Node* insert(Node* node, int start, int end) {
        if (node == nullptr) {
            Node* ins = new Node({start, end, nullptr, nullptr});
            if (root == nullptr) root = ins;
            return ins;
        }
        if (node->start > start) {
            Node* ins = insert(node->left, start, end);
            if (node->left == nullptr) {node->left = ins;}
            return ins;
        }
        Node* ins = insert(node->right, start, end);
        if (node->right == nullptr) {node->right = ins;}
        return ins;
    }
    
    bool overlaps(Node* node, int start, int end) {
        if (node == nullptr) return false;
        if (node->start >= end || node->end <= start) {
            // doesn't overlap with me, dig deeper
            if (node->start > start) {
                return overlaps(node->left, start, end);
            }
            return overlaps(node->right, start, end);
        }
        // overlaps with me, stop here
        return true;
    }
public:
    MyCalendar() {}
    
    bool book(int start, int end) {
        if (overlaps(root, start, end)) return false;
        insert(root, start, end);
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
