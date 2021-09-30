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
    ///////////////////////////////////////////////////////////////////////////////
    // O(n) space solution
    std::unordered_map<int, int> freqs;
    
    void traverse(TreeNode* root) {
        if (root->left) {
            traverse(root->left);
        }
        if (root->right) {
            traverse(root->right);
        }
        if (freqs.find(root->val) == freqs.end()) {
            freqs[root->val] = 1;
        } else {
            freqs[root->val]++;
        }
    }
    
    vector<int> findModeONSpace(TreeNode* root) {
        traverse(root);
        int max_freq = 0;
        vector<int> result;
        for (const pair<const int, int>& kv : freqs) {
            if (kv.second > max_freq) {
                max_freq = kv.second;
                result = {kv.first};
            } else if (kv.second == max_freq) {
                result.push_back(kv.first);
            }
        }
        return result;
    }
    ///////////////////////////////////////////////////////////////////////////////
    
    struct Candidates {
        int freq = 0;
        std::set<int> values;
    };
    
    // be careful about when this is called, 
    // do it only when mode in subtree is different from val
    int numOccurrences(TreeNode* root, int val) {
        if (root == nullptr) {
            return 0;
        }
        
        int sum = (root->val == val ? 1 : 0);
        if (root->left) {
            sum += numOccurrences(root->left, val);
        }
        if (root->right) {
            sum += numOccurrences(root->right, val);
        }
        return sum;
    }
    
    // returns all the candidates for this subtree, and the freq with which they occur
    Candidates findModeInternal(TreeNode* root) {
        Candidates left, right;
        if (root->left) {
            left = findModeInternal(root->left);
        }
        if (root->right) {
            right = findModeInternal(root->right);
        }
        
        // root->val is mode in left and right subtrees
        if (left.values.find(root->val) != left.values.end() &&
            right.values.find(root->val) != right.values.end()) {
            Candidates result;
            result.freq = left.freq + right.freq + 1;
            result.values = {root->val};
            return result;
        }
        
        // After this point, we have 3 candidates, left mode, right mode, and even possibly root val.
        // since root val can occur in both left and right subtrees, and together might add up.
        
        // root->val is mode in left subtree only.
        if (left.values.find(root->val) != left.values.end()) {
            left.values = {root->val};
            left.freq += 1 + numOccurrences(root->right, root->val);
        }
        
        // root->val is mode in right subtree only.
        if (right.values.find(root->val) != right.values.end()) {
            right.values = {root->val};
            right.freq += 1 + numOccurrences(root->left, root->val);
        }
        
        // root->val is mode in neither left nor right, it might still be mode.
        Candidates me;
        if (left.values.find(root->val) == left.values.end() &&
            right.values.find(root->val) == right.values.end()) {
            me.values = {root->val};
            me.freq = 1 + numOccurrences(root->left, root->val) + numOccurrences(root->right, root->val);
        }
        
        Candidates result = me;
        if (left.freq > result.freq) {
            result = left;
        } else if (left.freq == result.freq) {
            result.values.insert(left.values.begin(), left.values.end());
        }
        if (right.freq > result.freq) {
            result = right;
        } else if (right.freq == result.freq) {
            result.values.insert(right.values.begin(), right.values.end());
        }
        return result;
    }
    
    vector<int> findMode(TreeNode* root) {
        Candidates c = findModeInternal(root);
        vector<int> result;
        for (const int k : c.values) {
            result.push_back(k);
        }
        return result;
    }
};
