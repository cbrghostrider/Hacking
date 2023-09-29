class Solution {
    using Coord=pair<int, int>;
    
    int signature(const Coord& crd) {
        return ((crd.first << 16) | (crd.second));
    }
public:
    // O(n) time for simple BFS.
    int getFood(vector<vector<char>>& grid) {
        const int R=grid.size();
        const int C=grid[0].size();
        Coord source = {0, 0};        
                
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == '*') {source = {r, c}; break;}
            }
        }
        
        unordered_set<int> visited;
        std::queue<pair<Coord, int>> q;
        q.push({source, 0});
        visited.insert(signature(source));
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            Coord crd = elem.first;
            int dist  = elem.second;
            
            if (grid[crd.first][crd.second] == '#') {return dist;}
            
            vector<Coord> neighs = {
                {crd.first-1, crd.second}, {crd.first+1, crd.second}, 
                {crd.first, crd.second-1}, {crd.first, crd.second+1}
            };
            
            for (const Coord& neigh : neighs) {                
                if (neigh.first < 0 || neigh.first >= R || neigh.second < 0 || neigh.second >= C) continue;
                if (grid[neigh.first][neigh.second] == 'X') continue;
                int sig = signature(neigh);
                if (visited.find(sig) != visited.end()) continue;
                visited.insert(sig);
                
                q.push({neigh, dist+1});
            }
        }
        return -1;
    }
};
