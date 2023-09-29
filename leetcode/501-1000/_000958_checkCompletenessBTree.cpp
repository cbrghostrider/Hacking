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
        TreeNode* node;
        int seq;
    };
public:
    bool isCompleteTree(TreeNode* root) {
        // do a BFS and make sure every node has its expected seq number
        // any node n should have children (2n+1, 2n+2) in a full binary tree
        // (node, expected seq num for node)
        std::queue<Info> q;
        q.push({root, 0});
        
        int count=0;

        int expect_seq=0;
        while (!q.empty()) {
            auto elem = q.front(); q.pop(); 
            
            if (elem.seq != expect_seq) {
                return false;
            }
            expect_seq++;
            
            if (elem.node->left)  {q.push({elem.node->left,  elem.seq*2+1});}
            if (elem.node->right) {q.push({elem.node->right, elem.seq*2+2});}
        }
        return true;
    }
};
