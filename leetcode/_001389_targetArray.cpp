class Solution {
    struct Node {
        Node *next = nullptr;
        int value;
        ~Node() {delete next;}
    };
    Node *root = nullptr;
    
    void insert(int n, int position) {
        if (position == 0) {
            Node *node = new Node({root, n});
            root = node;
            return;
        }
        
        position--;
        Node *node = root;
        while (position != 0 && node != nullptr) {
            node = node->next;
            position--;
        }
        if (node) {
            Node* after = new Node({node->next, n});
            node->next = after;
        }
        return;
    }
    
 public:
    vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
        for (int i=0; i<nums.size(); i++) {
            insert(nums[i], index[i]);
        }
        vector<int> ans;
        Node *node = root;
        while (node) {
            ans.push_back(node->value);
            node = node->next;
        }
        delete root;
        return ans;
    }
};
