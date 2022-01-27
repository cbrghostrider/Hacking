class Solution {
    struct Node {
        int num  = -1;
        char tag = ' ';
        vector<Node*> children;
    };
    unordered_map<int, unordered_set<int>> connects;    
    vector<int> ans;
    
    void init(int n, vector<vector<int>>& edges, string labels) {        
        for (const vector<int>& edge : edges) {
            connects[edge[0]].insert(edge[1]);
            connects[edge[1]].insert(edge[0]);
        }        
        ans = vector<int>(n, 0);
    }
    
     unordered_map<char, int> traverse(const string& labels, int node) {        
        unordered_map<char, int> ret;
        ret[labels[node]] = 1;        
        
        for (int child : connects[node]) {
            connects[child].erase(node);  // remove parent association
            const auto& t = traverse(labels, child);
            for (const auto& kv : t) {
                ret[kv.first] += kv.second;
            }
        }
   
        ans[node] = ret[labels[node]];
        return ret;
    }
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        init(n, edges, labels);
        traverse(labels, 0);
        return ans;
    }
};
