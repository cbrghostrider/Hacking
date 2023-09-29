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
    
    bool isLeaf(TreeNode* node) {
        if (node == nullptr) return false;
        return node->left == nullptr && node->right == nullptr;
    }    
    
    struct Info {
        vector<int> lb;
        vector<int> rb;
        vector<int> leaves;
    };
    
    Info traverse(TreeNode* node, bool maintain_left, bool maintain_right) {
        if (node == nullptr) return Info();        
        if (isLeaf(node)) {
            return {{}, {}, {node->val}};
        }
        
        bool new_maintain_left  = maintain_left && node->left == nullptr;
        bool new_maintain_right = maintain_right && node->right == nullptr;
        
        Info lhs = traverse(node->left,  maintain_left,     new_maintain_right);
        Info rhs = traverse(node->right, new_maintain_left, maintain_right);
        
        Info ret;
        ret.leaves = lhs.leaves;
        if (rhs.leaves.size()) ret.leaves.insert(ret.leaves.end(), rhs.leaves.begin(), rhs.leaves.end());
        
        if (maintain_left) {
            if (node->left) {
                if (!isLeaf(node->left)) {ret.lb.push_back(node->left->val);}
                if (lhs.lb.size()) ret.lb.insert(ret.lb.end(), lhs.lb.begin(), lhs.lb.end());
            } else {
                if (!isLeaf(node->right)) {ret.lb.push_back(node->right->val);}
                if (rhs.lb.size()) ret.lb.insert(ret.lb.end(), rhs.lb.begin(), rhs.lb.end());
            }
        }

        if (maintain_right) {
            if (node->right) {
                if (!isLeaf(node->right)) {ret.rb.push_back(node->right->val);}
                if (rhs.rb.size()) ret.rb.insert(ret.rb.end(), rhs.rb.begin(), rhs.rb.end());
            } else {
                if (!isLeaf(node->left)) {ret.rb.push_back(node->left->val);}
                if (lhs.rb.size()) ret.rb.insert(ret.rb.end(), lhs.rb.begin(), lhs.rb.end());
            }
        }
        
        return ret;
    }
 public: 
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        if (root == nullptr) return {};
        Info lhs = traverse(root->left, true, false);
        Info rhs = traverse(root->right, false, true);
        
        vector<int> ans;
        ans.push_back(root->val);
        if (root->left) {
            if (!isLeaf(root->left)) ans.push_back(root->left->val);
            if (lhs.lb.size()) ans.insert(ans.end(), lhs.lb.begin(), lhs.lb.end());
        }
        if (lhs.leaves.size()) ans.insert(ans.end(), lhs.leaves.begin(), lhs.leaves.end());
        if (rhs.leaves.size()) ans.insert(ans.end(), rhs.leaves.begin(), rhs.leaves.end());
        if (root->right) {            
            if (rhs.rb.size()) ans.insert(ans.end(), rhs.rb.rbegin(), rhs.rb.rend());
            if (!isLeaf(root->right)) ans.push_back(root->right->val);
        }
        return ans;
    }
};
