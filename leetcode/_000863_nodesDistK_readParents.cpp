/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    vector<int> ans;
    unordered_map<TreeNode*, TreeNode*> parents;
    unordered_set<TreeNode*> done;

    void recordParents(TreeNode* node, TreeNode* from) {
        if (node == nullptr) return;
        parents[node] = from;
        recordParents(node->left, node);
        recordParents(node->right, node);
    }
    
    void descend(TreeNode* node, int k, int curr_depth) {
        if (node == nullptr) return;
        done.insert(node);
        if (curr_depth == k) {ans.push_back(node->val); return;}
        if (done.find(node->left) == done.end()) descend(node->left, k, curr_depth+1);
        if (done.find(node->right) == done.end()) descend(node->right, k, curr_depth+1);
        if (done.find(parents[node]) == done.end()) descend(parents[node], k, curr_depth+1);
    }
public:
    
    // This solution records all the parents, and then,
    // simply recurses directly from target, taking into account parent too.
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        recordParents(root, nullptr);
        descend(target, k, 0);
        return ans;
    }
};
