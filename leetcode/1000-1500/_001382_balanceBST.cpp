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
class Solution {
    unordered_map<int, vector<TreeNode*>> val_to_nodes;
    vector<int> vals;

    void recordTree(TreeNode* node) {
        if (node == nullptr) return;
        
        val_to_nodes[node->val].push_back(node);
        vals.push_back(node->val);
        recordTree(node->left);
        recordTree(node->right);
        node->left = node->right = nullptr;
    }
    
    TreeNode* getNode(int index) {
        TreeNode *node = val_to_nodes[vals[index]].back();
        val_to_nodes[vals[index]].pop_back();
        return node;
    }
    
    // constructs a balanced BST for indices [left, right]
    TreeNode* constructTree(int left, int right) {
        if (left == right) {
            return getNode(left);
        }
        
        if (left + 1 == right) {
            TreeNode *node = getNode(left);
            node->right = getNode(right);
            return node;
        }
        
        int mid = (left+right)/2;
        int midMinus = mid-1;
        int midPlus = mid+1;
        TreeNode *me = getNode(mid);
        TreeNode *ltree = constructTree(left, midMinus);
        TreeNode *rtree = constructTree(midPlus, right);
        me->left = ltree;
        me->right = rtree;
        return me;
    }
    
public:  
    TreeNode* balanceBST(TreeNode* root) {
        recordTree(root);
        std::sort(vals.begin(), vals.end());
        return constructTree(0, vals.size()-1);
    }
};
