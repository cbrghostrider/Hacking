class KthLargest {
public:
    ///////////////////////////////////////////////////////////////////////////
    // WITHOUT using priority queue
    // non-balanced BST
    // O(n) worst case time and space.
    ///////////////////////////////////////////////////////////////////////////
    struct TreeNode {
        TreeNode *left;
        TreeNode *right;
        int val;       // val of the subtree node
        int num_val;   // num of occurrences of val
        int size;      // size of the subtree rooted here, including all occurrences of val
        TreeNode(int val) : left(nullptr), right(nullptr), val(val), num_val(1), size(1) {}
    };
    
    TreeNode *tree = nullptr;
    int kth = 0;
    
    void addTree(TreeNode *root, int val) {
        if (root == nullptr) {
            tree = new TreeNode(val);
            return;
        }
        
        root->size++;
        
        if (root->val == val) {
            root->num_val++;
            return;
        }
        if (root->val > val) {
            if (root->left == nullptr) {
                root->left = new TreeNode(val);
            } else {
                addTree(root->left, val);
            }
            return;
        }
        if (root->right == nullptr) {
            root->right = new TreeNode(val);
            return;
        }
        addTree(root->right, val);
    }
    
    int findKthLargest(TreeNode* root, int k) {
        int greater = (root->right == nullptr) ? 0 : root->right->size;
        if (greater >= k) {
            return findKthLargest(root->right, k);
        }
        if (greater + root->num_val >= k) {
            return root->val;
        }
        return findKthLargest(root->left, k - greater - root->num_val);
    }
    
    /*
    KthLargest(int k, vector<int>& nums) {
        kth = k;
        for (int n : nums) {
            addTree(tree, n);
        }
    }
    
    int add(int val) {
        addTree(tree, val);
        return findKthLargest(tree, kth);
    }
    */
    
    ///////////////////////////////////////////////////////////////////////////
    // using priority queue, keep only k largest elements at any time
    // O(k) space and O(log k) time since priority queue is balanced
    ///////////////////////////////////////////////////////////////////////////
    std::priority_queue<int, std::vector<int>, std::greater<int> > min_heap;
    int kval = 0;
    
    KthLargest(int k, vector<int>& nums) {
        kval = k;
        for (int n : nums) {
            min_heap.push(n);
        }
        
        // remove enough elements such that only k remain
        while (min_heap.size() > kval) {
            min_heap.pop();
        }
    }
    
    int add(int val) {
        if (min_heap.size() < kval) {
            min_heap.push(val);
        } else {
            if (min_heap.top() < val) {
                min_heap.pop();
                min_heap.push(val);
            }
        }
        return min_heap.top();
    }
    
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
