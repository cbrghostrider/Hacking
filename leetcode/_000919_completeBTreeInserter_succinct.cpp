/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// 
// This version is slower and takes up more space.
// O(n) both time and space for insert. 
// O(1) for get root.
// However it is much easier to understand.
//
// It is based on bfs, where we store the entire last 2 levels, and might need to copy them during insert.
//
class CBTInserter {
    TreeNode* root = nullptr;
    vector<TreeNode*> leaves, parents;  // stores ultimate and penultimate levels of the tree
    int depth = -1; // the depth that will be filled in
    
    // Finds the depth of the full binary tree.
    void computeDepth() {
        depth=-1;
        TreeNode* node = root;
        while (node) {
            depth++;
            node = node->left;
        }
    }
    
    // populates the leaves' and their parents' level
    void initialize() {
        computeDepth();
        std::queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        
        while (!q.empty()) {
            pair<TreeNode*, int> item = q.front();
            q.pop();
            if (item.first->left) {q.push({item.first->left, item.second+1});}
            if (item.first->right) {q.push({item.first->right, item.second+1});}
            
            if (item.second == depth-1) {parents.push_back(item.first);}
            if (item.second == depth) {leaves.push_back(item.first);}
        }
    
        nextLevelIfNeeded();
    }
    
    void nextLevelIfNeeded() {
        if (pow(2, depth) == leaves.size()) {  // fully filled
            parents = leaves;
            leaves.clear();
            depth++;
        }
    }
    
public:
    CBTInserter(TreeNode* r) : root(r) {
        if (r == nullptr) return;
        initialize();
    }
    
    // O(n) space, O(n) time for the copy if needed.
    int insert(int val) {
        TreeNode* node = new TreeNode(val);
        if (root == nullptr) {
            root = node;
            initialize();
            return -1;  // no parent val
        }
        
        vector<TreeNode*>& p=parents, l=leaves;
        int index = leaves.size()/2;
        int retval=0;
        if (parents[index]->left == nullptr) {
            parents[index]->left = node;
            retval = parents[index]->val;
        } else {
            parents[index]->right = node;
            retval = parents[index]->val;
        }
        leaves.push_back(node);
        
        nextLevelIfNeeded();
        return retval;
    }
    
    TreeNode* get_root() {
        return root;
    }
};

