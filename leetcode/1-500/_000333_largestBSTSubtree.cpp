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
    struct Info {
        int smallest=std::numeric_limits<int>::max();
        int largest=std::numeric_limits<int>::min();
        bool is_bst=true;
        int best_size=0;        // the size of the largest bst in this subtree (may be itself)
    };
    
    Info traverse(TreeNode* node) {
        if (node == nullptr) return Info();
        
        Info lhs = traverse(node->left);
        Info rhs = traverse(node->right);
        
        Info ret;
        ret.smallest = std::min(node->val, std::min(lhs.smallest, rhs.smallest));
        ret.largest = std::max(node->val, std::max(lhs.largest, rhs.largest));
        ret.is_bst = lhs.is_bst && rhs.is_bst && (node->val > lhs.largest) && (node->val < rhs.smallest);
        
        if (ret.is_bst) {
            ret.best_size = 1 + lhs.best_size + rhs.best_size;
        } else {
            ret.best_size = std::max(lhs.best_size, rhs.best_size);                   
        }
        
        return ret;
    }
public:
    int largestBSTSubtree(TreeNode* root) {
        Info info = traverse(root);
        return info.best_size;
    }
};
