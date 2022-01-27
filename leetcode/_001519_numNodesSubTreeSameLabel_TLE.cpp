class Solution {
    struct Node {
        int num  = -1;
        char tag = ' ';
        vector<Node*> children;
    };
    unordered_map<int, unordered_set<int>> connects;
    unordered_map<int, Node*> nodes;
    vector<int> ans;
    
    void init(int n, vector<vector<int>>& edges, string labels) {
        for (int i=0; i<n; i++) {
            Node* node = new Node();
            node->num = i;
            node->tag = labels[i];
            nodes[i] = node;
        }
        
        for (const vector<int>& edge : edges) {
            connects[edge[0]].insert(edge[1]);
            connects[edge[1]].insert(edge[0]);
        }        
                
        vector<int> process;
        process.push_back(0);
        
        while (!process.empty()) {
            int num = process.back();
            process.pop_back();
            Node* me = nodes[num];
            
            for (int child : connects[num]) {
                process.push_back(child);
                me->children.push_back(nodes[child]);
                connects[child].erase(num);
            }
        }        
        ans = vector<int>(n, 0);
    }
    
    unordered_map<char, int> traverse(Node* node) {
        if (node == nullptr) return {};
        unordered_map<char, int> ret;
        ret[node->tag] = 1;        
        
        for (Node* child : node->children) {
            const auto& t = traverse(child);
            for (const auto& kv : t) {
                ret[kv.first] += kv.second;
            }
        }
   
        ans[node->num] = ret[node->tag];
        return ret;
    }
public:
    // Functionally correct, but gets TLE.
    // Need to not bother building the actual tree from nodes, but just work with edges directly.
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        init(n, edges, labels);
        traverse(nodes[0]);
        return ans;
    }
};
