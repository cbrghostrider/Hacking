class Solution {
    unordered_map<int, unordered_set<int>> out_vertices;
    unordered_map<int, bool> visited;
    int last_node=-1;
    int max=-1;
    
    void bfs(int start) {
        visited.clear();
        std::queue<pair<int, int>> q;
        q.push({start, 0});
        visited[start] = true;
        
        while (!q.empty()) {
            auto n_l = q.front(); q.pop();
            int n = n_l.first;
            int l = n_l.second;
            last_node = n;  // memorize every time
            
            for (int v : out_vertices[n]) {
                if (visited[v]) continue;
                q.push({v, l+1});
                visited[v] = true;
                if (l+1 > max) {max = l+1;}
            }
        }
    }

public:
    // when we run bfs from any node, the last level will certainly contain an "extreme" node (i.e. end of max_path)
    // then we run bfs again, starting from this last_node, and that gives us the true max_path
    // O(n) time for 2 bfs runs.
    int treeDiameter(vector<vector<int>>& edges) {
        for (const auto& e : edges) {
            out_vertices[e[0]].insert(e[1]);
            out_vertices[e[1]].insert(e[0]);
        }
        
        bfs(0);  // finds the last_node, which is one of the end nodes of max_path 
        bfs(last_node);  // finds the max path
        
        return max;
    }
};
