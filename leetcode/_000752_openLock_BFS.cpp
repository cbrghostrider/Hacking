class Solution {
    struct Node {
        int val;
        string code;
        bool visited;
        vector<int> conns;
    };
    
    unordered_map<char, char> succs = {
        {'0', '1'}, {'1', '2'}, {'2', '3'}, {'3', '4'}, {'4', '5'}, 
        {'5', '6'}, {'6', '7'}, {'7', '8'}, {'8', '9'}, {'9', '0'}
    };
    
    vector<Node*> nodes;
    unordered_map<string, int> cton;  // code to node
    unordered_set<string> deadends;
    
    // Adds leading 0's if needed
    string toStr(int i) {
        string ret = std::to_string(i);
        int len = 4 - ret.size();
        string prefix = string(len, '0');
        return (prefix + ret);
    }
    
    // will be called for index=0...3 
    // will rotate that dial and return the code
    string succ(const string& code, int index) {
        string ret = code;
        ret[index] = succs[ret[index]];
        return ret;
    }
    
    void buildGraph() {
        for (int n=0; n<10000; n++) {
            Node* node = nodes[n];
            if (deadends.find(node->code) != deadends.end()) {
                continue;  // this is shunned
            }
            string d0 = succ(node->code, 0);
            string d1 = succ(node->code, 1);
            string d2 = succ(node->code, 2);
            string d3 = succ(node->code, 3);
            
            if (deadends.find(d0) == deadends.end()) {
                node->conns.push_back(cton[d0]);
                nodes[cton[d0]]->conns.push_back(n);
            }            
            if (deadends.find(d1) == deadends.end()) {
                node->conns.push_back(cton[d1]);
                nodes[cton[d1]]->conns.push_back(n);
            }            
            if (deadends.find(d2) == deadends.end()) {
                node->conns.push_back(cton[d2]);
                nodes[cton[d2]]->conns.push_back(n);
            }            
            if (deadends.find(d3) == deadends.end()) {
                node->conns.push_back(cton[d3]);
                nodes[cton[d3]]->conns.push_back(n);
            }
        }
    }
    
public:
    int openLock(vector<string>& des, string target) {
        // Initialization.
        for (const string& d : des) {deadends.insert(d);}
        for (int i=0; i<10000; i++) {
            string code = toStr(i);
            Node *node = new Node({i, code, false, {}});
            nodes.push_back(node);
            cton[code] = i;
        }
        
        // Build the graph.
        buildGraph();
        
        // BFS to try and find target from source.
        // (node, moves) is stored
        queue<pair<Node*, int>> q;
        q.push({nodes[0], 0});
        nodes[0]->visited = true;
        
        while (!q.empty()) {
            auto elem = q.front();
            Node* node = elem.first;
            int dist = elem.second;
            q.pop();
            
            if (node->code == target) return dist;
            
            for (int n : node->conns) {
                if (nodes[n]->visited) continue;
                nodes[n]->visited = true;
                q.push({nodes[n], dist+1});
            }
        }
        return -1;
    }
};
