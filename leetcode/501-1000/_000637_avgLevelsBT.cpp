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
    
    struct Node {
        int level = -1;
        TreeNode* node = nullptr;
    };
    
    std::deque<Node> nodes;
    
public:
    
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> result;
        nodes.push_back(Node{0, root});
        
        while (!nodes.empty()) {
            int level = nodes.front().level;
            double sum_level = 0;
            int num_level = 0;
            while (!nodes.empty() && nodes.front().level == level) {
                Node node = nodes.front();
                sum_level += node.node->val;
                num_level += 1;
                if (node.node->left) {
                    nodes.push_back({level + 1, node.node->left});
                }
                if (node.node->right) {
                    nodes.push_back({level + 1, node.node->right});
                }
                nodes.pop_front();
            }
            double avg_level = sum_level / (double)num_level;
            result.push_back(avg_level);
        }
        
        return result;
    }
};
