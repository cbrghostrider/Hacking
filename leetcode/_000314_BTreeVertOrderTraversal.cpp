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
    // Treat a left  as -1 turn.
    // Treat a right as +1 turn.
    // Write my location first, then look left, then look right.
    // Need to perform BFS because levels closer to root need to be written first.
    
    // We store the "column" in a map, because it can have negative keys (all lefts for e.g.)
    // later we re-map the negative keys to 0-based keys for output
    map<int, vector<int>> vorder;
    
public:
    
    struct Info {
        TreeNode* node=nullptr;
        int turns=0;
    };

    // O(n log n) time: n nodes visited, log n per map operation.
    // O(n) space, to store info about n nodes in the map (total).
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (root == nullptr) return {};
        
        // Perform BFS.
        std::queue<Info> q;
        q.push({root, 0});
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            vorder[elem.turns].push_back(elem.node->val);
            
            if (elem.node->left) q.push({elem.node->left, elem.turns-1});
            if (elem.node->right) q.push({elem.node->right, elem.turns+1});
        }
        
        // re-map negative keys to 0-based for output
        vector<vector<int>> ans(vorder.size(), vector<int>());
        auto it=vorder.begin();
        auto zero_index = it->first;
        for (; it != vorder.end(); it++) {
            int index = it->first - zero_index;
            ans[index] = it->second;
        }
        return ans;
    }
};
