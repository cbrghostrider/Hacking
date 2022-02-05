class Solution {
    struct Node {
        // This node is for all unit segments from those that 
        // end at start, to those that end at end.
        int start=0;     // inclusive (unit segment ending at start)
        int end=0;       // inclusive (unit segment ending at end)
        int occupied=0;  // how many unit segments already filled in
        Node *left  = nullptr;  // left half of the range here
        Node *right = nullptr;  // right half of the range here
    };
    
    Node* root=nullptr;  
    
    // returns how many locations were filled in
    int Paint(Node* node, int start, int end) {
        
        if (start > node->end || end < node->start) {
            // Out of bounds, nothing to do.
            return 0;
        }
        
        start = std::max(node->start, start);
        end = std::min(node->end, end);
        
        int capacity = node->end-node->start+1;
        if (node->occupied == capacity) {return 0;}
        
        if (node->end == node->start) {
            // Unit segment, don't recurse further
            node->occupied = 1;
            return 1;  
        }
        
        int mid = (node->start+node->end)/2;
        int midplus = mid+1;
        
        // recurse
        if (node->left == nullptr) {
            node->left = new Node();
            node->left->start = node->start;
            node->left->end = mid;
        }
        if (node->right == nullptr) {
            node->right = new Node();
            node->right->start = midplus;
            node->right->end = node->end;
        }
        
        int lhs = Paint(node->left, start, end);
        int rhs = Paint(node->right, start, end);
        
        node->occupied = node->left->occupied + node->right->occupied;
        return lhs+rhs; 
    }
    
public:
    // O(k + n log k) time, O(k) space.
    // n = |paint| vector
    // k = |range of segment|  i.e. max end - min start
    vector<int> amountPainted(vector<vector<int>>& paint) {
        root = new Node();
        root->start = 1;
        root->end = (1 << 16);
        
        vector<int> ans;
        for (const vector<int>& seg : paint) {
            int start = seg.at(0) + 1;
            int end = seg.at(1);
            int filled = Paint(root, start, end);
            ans.push_back(filled);
        }
        return ans;
    }
};
