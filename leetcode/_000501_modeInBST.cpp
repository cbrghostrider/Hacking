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
    // O(n) space
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
    
    ////////////////////////////////////////////////////////////////////////////
    // O(1) space
    // In order traversal will visit values in ascending order. So keep a running
    // count of the current value. When value changes, adjust maxCount encountered,
    // and adjust answer as needed.
    
    int currVal = std::numeric_limits<int>::min();
    int currCount = 0;
    int maxCount = 0;
    vector<int> answers = {};
    
    void handle(int val) {
        if (val == currVal) {
            currCount++;
        } else {
            currVal = val;
            currCount = 1;
        }
        
        if (currCount == maxCount) {
            answers.push_back(val);
        } else if (currCount > maxCount) {
            maxCount = currCount;
            answers = {val};
        }
    }
    
    void traverseInOrder(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        
        traverseInOrder(root->left);
        handle(root->val);
        traverseInOrder(root->right);
    }
    
    
    vector<int> findMode(TreeNode* root) {
        traverseInOrder(root);
        return answers;
    }
};
