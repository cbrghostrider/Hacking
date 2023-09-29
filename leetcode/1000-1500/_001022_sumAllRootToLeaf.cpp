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
    vector<int> path;
    int sum = 0;
    
    // returns the integer value of path currently in "path"
    int integerify() {
        double exp = 0;
        long num = 0;
        for (int i = path.size() - 1; i>= 0; i--) {
            if (path[i]) {
                num += (long)(path[i] * pow(2.0, exp));
            }
            exp += 1.0;
        }
        return num;
    }
    
    void traverse(TreeNode* root) {
        if (root == nullptr) return;
        path.push_back(root->val);
        
        if (root->left == nullptr && root->right == nullptr) {  // leaf node.
            sum += integerify();
            path.pop_back();
            return;
        }
        
        traverse(root->left);
        traverse(root->right);
        path.pop_back();
        return;
    }
    
public:
    int sumRootToLeaf(TreeNode* root) {
        traverse(root);
        return sum;
    }
};
