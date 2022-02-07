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
        bool is_bst = false;
        int my_sum=0;
        int my_max=std::numeric_limits<int>::min();
        int my_min=std::numeric_limits<int>::max();        
        int max_sum=std::numeric_limits<int>::min();  // max sum for recursive under this node
    };
    
    Info traverse(TreeNode* node) {        
        Info info;
        if (node == nullptr) {
            info.is_bst = true;
            return info;
        }
        
        Info lhs = traverse(node->left);
        Info rhs = traverse(node->right);
        
        info.my_max = std::max(std::max(lhs.my_max, rhs.my_max), node->val);
        info.my_min = std::min(std::min(lhs.my_min, rhs.my_min), node->val);
        info.my_sum = node->val + lhs.my_sum + rhs.my_sum;
        
        bool lhs_ok = node->left == nullptr  || node->val > lhs.my_max;
        bool rhs_ok = node->right == nullptr || node->val < rhs.my_min;
        
        info.max_sum = std::max(lhs.max_sum, rhs.max_sum);
        if (lhs.is_bst && rhs.is_bst && lhs_ok && rhs_ok) {
            info.is_bst = true;
            info.max_sum = std::max(info.max_sum, info.my_sum);
        }
        
        return info;
    }
public:
    // O(n) time to visit all nodes, 
    // O(h) space for stack recursion.
    int maxSumBST(TreeNode* root) {
        Info info = traverse(root);
        if (info.max_sum < 0) return 0;  // nullptr leaf child will have sum 0, which is max
        return info.max_sum;
    }
};
