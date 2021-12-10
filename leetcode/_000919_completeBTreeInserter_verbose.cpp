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
// This version is faster and takes up lesser space.
// O(log n) both time and space for insert, 
// O(1) for get root.
// However it is much more cryptic to understand.
//
// It is based on dfs, where we store the non-leaf-path, and rewind along that as needed.
//
class CBTInserter {
    TreeNode* root = nullptr;
    vector<TreeNode*> non_leaf_path;  // path all the way to the last non-leaf node, where stuff needs to be added
    TreeNode* last_leaf;
    int level = -1;
    
    // if called without the optional arguments, it simply finds the last leaf
    // if called with the optional arguments, it constructs the path leading up to the last leaf (but not including it)
    bool dfs(TreeNode* node, int from_level, bool break_at_node=false, TreeNode* check=nullptr) {
        int my_level = from_level + 1;
        if (node->left == nullptr && node->right == nullptr) {
            if (my_level < level) return check == node;
            level = my_level;
            last_leaf = node;
            return check == node;
        }
        non_leaf_path.push_back(node);
        bool done = false;
        if (node->left) {
            done = dfs(node->left, my_level, break_at_node, check);
        }
        if (done) return done;
        if (node->right) {
            done = dfs(node->right, my_level, break_at_node, check);
        }
        if (done) return done;
        non_leaf_path.pop_back();
        return check == node;
    }
    
    // constructs a new non_leaf_path, which is simply the left nodes
    // this is basically called when a level is filled up
    void reinitialize() {
        non_leaf_path.clear();
        TreeNode* node = root;
        while (node) {
            non_leaf_path.push_back(node);
            node = node->left;
        }
    }
    
public:
    CBTInserter(TreeNode* r) : root(r) {
        if (r == nullptr) return;
        dfs(r, -1);  // find the last leaf
        int llval = last_leaf->val;
        non_leaf_path.push_back(root);
        dfs(r, -1, true, last_leaf);  // construct path leading up to last leaf (but not including)
        int llpval = non_leaf_path.back()->val;
        int some=1;
    }
   
    // O(log n) space, O(log n) time. 
    int insert(int val) {
        TreeNode* new_leaf = new TreeNode(val);
        
        if (root == nullptr) {
            root = last_leaf = new_leaf;
            reinitialize();
            return -1;
        }
        
        if (!non_leaf_path.empty()) {
            if (non_leaf_path.back()->left == nullptr) {
                non_leaf_path.back()->left = last_leaf = new_leaf;
                return non_leaf_path.back()->val;
            } else if (non_leaf_path.back()->right == nullptr) {
                non_leaf_path.back()->right = last_leaf = new_leaf;
                return non_leaf_path.back()->val;
            }
        }
        TreeNode *check = last_leaf;
        while (!non_leaf_path.empty() && non_leaf_path.back()->right == check) {
            check = non_leaf_path.back();
            non_leaf_path.pop_back();
        }
        if (!non_leaf_path.empty()) {
            if (check == non_leaf_path.back()->left) {
                non_leaf_path.push_back(non_leaf_path.back()->right);
            } else {
                non_leaf_path.push_back(non_leaf_path.back()->left);
            }
        } else {
            reinitialize();
        }
        return insert(val);  // will only recurse once, guaranteed
    }
    
    // O(1) time.
    TreeNode* get_root() {
        return root;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
