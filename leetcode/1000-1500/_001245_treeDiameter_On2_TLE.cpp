class Solution {
    unordered_map<int, unordered_set<int>> out_vertices;
    unordered_map<int, bool> visited;
    
    int dfs(int vertex) {
        int max_path=0;
        for (int v : out_vertices[vertex]) {
            if (visited[v]) continue;
            visited[v] = true;
            int my_path = 1 + dfs(v);
            if (my_path > max_path) {max_path = my_path;}
        }
        return max_path;
    }

public:
    // Since it is a "tree", the longest path will start and end at the leaves, not at the intermediate nodes.
    // so candidates for begin and end nodes are only those vertices with degree=1
    // can perform dfs at each end node, to figure out the max depth for each end node
    // then take the max max_depth globally, which is the diameter
    //
    // O(n^2) time, O(n) space.
    // Runs into TLE.
    int treeDiameter(vector<vector<int>>& edges) {
        for (const auto& e : edges) {
            out_vertices[e[0]].insert(e[1]);
            out_vertices[e[1]].insert(e[0]);
        }
        
        int diameter=0;
        for (const auto& kv : out_vertices) {
            if (kv.second.size() != 1) continue;
            
            visited.clear();
            visited[kv.first] = true;
            int my_max = dfs(kv.first);
            if (my_max > diameter) {diameter = my_max;}
        }
        
        return diameter;
    }
};
