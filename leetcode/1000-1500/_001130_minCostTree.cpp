class Solution {
    struct TreeNode {
        int max_leaf = 0;          // Stores max leaf value for my left/right subtrees.
        int prod = 0;              // Stores prod of my left-max-leaf * right-max-leaf.
        int sum_non_leaves = 0;    // Stores sum of non-leaves for me (including my prod).
        TreeNode* left = nullptr;  // My left subtree.
        TreeNode* right = nullptr; // My right subtree.
    };
    
    // Signature for hash of trees formed between indices i and j.
    int signature(int i, int j) {
        return ((i << 16) | j);
    }
    
    // stores min cost candidate tree for arr[i, j]
    unordered_map<int, TreeNode*> treeCache;
    vector<int> arr;
    
    TreeNode* createNode(TreeNode* left, TreeNode* right) {
        TreeNode *me = new TreeNode(); 
        me->left = left; me->right = right;
        me->max_leaf = std::max(me->left->max_leaf, me->right->max_leaf);
        me->prod = me->left->max_leaf * me->right->max_leaf;
        me->sum_non_leaves = me->prod + me->left->sum_non_leaves + me->right->sum_non_leaves;
        return me;
    }
    
    // Uses DP to create all trees.
    // O(n^3) time, O(n^2) space.
    void populateAllTrees() {
        // Base case, size 1 sub-arrays.
        for (int i=0; i<arr.size(); i++) {
            int sig = signature(i, i);
            TreeNode* me = new TreeNode();
            me->max_leaf = arr[i];
            treeCache[sig] = me;
        }
        
        // Base case, size 2 sub-arrays.
        for (int i=0; i<arr.size()-1; i++) {
            int sig = signature(i, i+1);
            TreeNode *left = treeCache[signature(i, i)];
            TreeNode *right = treeCache[signature(i+1, i+1)];
            TreeNode *me = createNode(left, right);
            treeCache[sig] = me;
        }
        
        // Recursive case, all other sized trees.
        for (int tsz=3; tsz<=arr.size(); tsz++) {
            for (int i=0; i<=arr.size()-tsz; i++) {
                // Construct all trees of size tsz, starting at index i
                int sig = signature(i, i+tsz-1);
                
                int min_cost = std::numeric_limits<int>::max();
                for (int brk=i; brk<i+tsz-1; brk++) {
                    TreeNode* left_tree = treeCache[signature(i, brk)];
                    TreeNode* right_tree = treeCache[signature(brk+1, i+tsz-1)];
                    
                    TreeNode *node = createNode(left_tree, right_tree);
                    if (node->sum_non_leaves < min_cost) {
                        min_cost = node->sum_non_leaves;
                        treeCache[sig] = node;
                    }
                } 
            }
        }
    }
    
public:
    int mctFromLeafValues(vector<int>& a) {
        arr = a;
        populateAllTrees();
        return treeCache[signature(0, a.size()-1)]->sum_non_leaves;
    }
};
