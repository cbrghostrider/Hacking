class Solution {
    std::unordered_map<int, vector<int>> connections;
    std::vector<bool> visited;
public:
    bool validPath(int n, vector<vector<int>>& edges, int start, int end) {
        visited = std::vector<bool>(n, false);
        for (const vector<int>& edge : edges) {
            connections[edge[0]].push_back(edge[1]);
            connections[edge[1]].push_back(edge[0]);
        }
        
        vector<int> stack;
        stack.push_back(start);
        visited[start] = true;
        
        while (!stack.empty()) {
            int vertex = stack.back();
            stack.pop_back();
            if (vertex == end) {return true;}
            
            for (int c : connections[vertex]) {
                if (!visited[c]) {
                    visited[c] = true;
                    stack.push_back(c);
                }
            }
            
        }
        return false;
    }
};
