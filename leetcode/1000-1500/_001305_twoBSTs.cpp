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
public:
    void visit(TreeNode* root, vector<int>& elems) {
        if (root == nullptr) return;
        elems.push_back(root->val);
        visit(root->left, elems);
        visit(root->right, elems);
    }
    
    // O(n log n) time, O(n) space.
    vector<int> getAllElements_vect(TreeNode* root1, TreeNode* root2) {
        vector<int> elems;
        visit(root1, elems);
        visit(root2, elems);
        std::sort(elems.begin(), elems.end()); 
        return elems;
    }

    vector<int> ans;
    
    void initStack(TreeNode *node, vector<TreeNode*>& stack) {
        while (node) {stack.push_back(node); node = node->left;}
    }
    
    // Solution that visits both trees in parallel.
    // O(n) time.
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> ans;
        vector<TreeNode*> stack1, stack2;
        
        initStack(root1, stack1);
        initStack(root2, stack2);

        while (!stack1.empty() || !stack2.empty()) {
            TreeNode* n1 = stack1.empty() ? nullptr : stack1.back();
            TreeNode* n2 = stack2.empty() ? nullptr : stack2.back();
            
            bool choose1 = n1 != nullptr && (n2 == nullptr || n1->val < n2->val);
            
            if (choose1) {
                ans.push_back(n1->val);
                stack1.pop_back();
                if (n1->right) initStack(n1->right, stack1);
            } else {
                ans.push_back(n2->val);
                stack2.pop_back();
                if (n2->right) initStack(n2->right, stack2);
            }
        }
        return ans;
    }
    
};
