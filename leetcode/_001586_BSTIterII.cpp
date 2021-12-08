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
class BSTIterator {
    vector<TreeNode*> stack;
    vector<TreeNode*> undos;

    // pushes all the left elements of root recursively.
    void unroll(TreeNode* root) {
        while (root) {
            stack.push_back(root);
            root = root->left;
        }
    }
    
    // undoes an unroll
    void ununroll(TreeNode* node) {
        if (node->right == nullptr) {
            stack.push_back(node);
            return;
        }
        
        int ind=stack.size()-1;
        while (ind >= 0) {
            if (stack[ind] == node->right) {break;}
            ind--;
        }
        if (ind >= 0) {
            for (int i=stack.size()-1; i>=ind; i--) {
                stack.pop_back();
            }
        }
        stack.push_back(node);
    }
    
 public:
    BSTIterator(TreeNode* root) {
        unroll(root);
    }
    
    bool hasNext() {
        return !stack.empty();
    }
    
    int next() {
        // Problem statement assumes that call is always valid.
        TreeNode* node = stack.back();
        int ret = node->val;
        TreeNode* right = node->right;
        stack.pop_back();  // remove node just read
        undos.push_back(node);
        if (right) {unroll(right);}
        return ret;
    }
    
    bool hasPrev() {
        return (undos.size() > 1);
    }
    
    int prev() {
        // Problem statement assumes that call is always valid.
        TreeNode *node = undos.back();
        undos.pop_back();
        ununroll(node);
        return undos.back()->val;
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * bool param_1 = obj->hasNext();
 * int param_2 = obj->next();
 * bool param_3 = obj->hasPrev();
 * int param_4 = obj->prev();
 */
