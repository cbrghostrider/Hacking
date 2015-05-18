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
    typedef pair<int, TreeNode*> LvlNode;
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> levelOrd;
        if (root == NULL) return levelOrd;
        
        deque<LvlNode> lvlNodes;
        lvlNodes.push_back(make_pair(0, root));
        
        while (!lvlNodes.empty()) {
            LvlNode lnode = lvlNodes.front(); lvlNodes.pop_front();
            if (levelOrd.size() <= lnode.first) {
                levelOrd.push_back(vector<int>());
            }
            levelOrd[lnode.first].push_back(lnode.second->val);
            if (lnode.second->left) {
                lvlNodes.push_back(make_pair(lnode.first + 1, lnode.second->left));
            }
            if (lnode.second->right) {
                lvlNodes.push_back(make_pair(lnode.first + 1, lnode.second->right));
            }
        }
        std::reverse(levelOrd.begin(), levelOrd.end());
        return levelOrd;
    }
};
