class Solution {
    vector<vector<int>> adj_list;   
    int N;
    
    unordered_map<int, vector<vector<int>>> paths;
    
    vector<vector<int>> getPaths(int from) {
        if (paths.find(from) != paths.end()) return paths[from];
        if (from == N-1) {
            paths[N-1] = {{N-1}};
            return paths[N-1];
        }
        
        vector<vector<int>> my_paths;
        for (int neigh : adj_list[from]) {
            vector<vector<int>> ahead = getPaths(neigh);
            for (auto& path : ahead) {
                path.push_back(from);
            }
            my_paths.insert(my_paths.end(), ahead.begin(), ahead.end());
        }
        
        paths[from] = my_paths;
        return my_paths;
    }
    
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        adj_list = graph;
        N = adj_list.size();
        
        vector<vector<int>> ans = getPaths(0);
        for (auto& path : ans) {
            std::reverse(path.begin(), path.end());
        }
        return ans;
    }
};
