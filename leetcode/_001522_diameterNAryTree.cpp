/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    
    // returns (height, longest_path) for tree starting at root
    pair<int, int> getData(Node* root) {
        if (root == nullptr) return make_pair(0, 0);
        if (root->children.size() == 0) return make_pair(0, 0);
        
        // the longest path will either include root, or just be the longest path of one of its subtrees
        vector<pair<int, int>> subtree_ans;
        int max_path_child = 0;
        for (int i=0; i<root->children.size(); i++) {
            auto ans = getData(root->children[i]);
            subtree_ans.push_back(ans);
            if (ans.second > max_path_child) {max_path_child = ans.second;}
        }
        std::sort(subtree_ans.begin(), subtree_ans.end(), 
                  [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs)->bool {
            return (lhs.first > rhs.first);
        });
        int path_thru_me = (root->children.size() == 1 
                            ? 1 + subtree_ans[0].first 
                            : 2 + subtree_ans[0].first + subtree_ans[1].first);
        int max_path = std::max(path_thru_me, max_path_child);
        int max_height = 1 + (root->children.size() == 0 ? 0 : subtree_ans[0].first);
        return make_pair(max_height, max_path);
    }
    
    int diameter(Node* root) {
        auto ans = getData(root);
        return ans.second;
    }
};
