struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {
        return (r == rhs.r && c == rhs.c);
    }
};

template<>
struct hash<Coord> {
size_t operator()(const Coord& coord) const {
    return ((coord.r << 16) | (coord.c));
}
};

// key: dist
// value: obstacles leftover to destroy
using Info = pair<int, int>;

class Solution {
    
public:
    // O(R*C*k) time, O(R*C*k) space.
    int shortestPath(vector<vector<int>>& grid, int k) {
        const int R=grid.size();
        const int C=grid[0].size();
        
        // -1 is unvisited, 
        // if visited, stores min dist for that [r][c][obstacles]
        vector<vector<vector<int>>> visited(R, vector<vector<int>>(C, vector<int>(1+k, -1)));
        
        queue<pair<Coord, Info>> q;
        q.push({{0, 0}, {0, k}});    
        visited[0][0][k] = 0;
        
        int best = std::numeric_limits<int>::max();
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            Coord crd = elem.first;
            const Info& info = elem.second;     
            int dist = info.first;
            int obstacles = info.second;
            
            if (crd.r == R-1 && crd.c == C-1) {
                best = std::min(best, info.first);
                // Don't recurse after the end.
                continue;
            }
            
            if (dist > best) {
                // this can't possibly be better
                continue;  
            }
            
            vector<Coord> neighs = {
                {crd.r-1, crd.c}, {crd.r+1, crd.c},
                {crd.r, crd.c-1}, {crd.r, crd.c+1}
            };
            
            for (const Coord& neigh : neighs) {
                if (neigh.r < 0 || neigh.r >= R || neigh.c < 0 || neigh.c >= C) continue;                
                
                int my_obstacles = obstacles - grid[neigh.r][neigh.c];                
                int my_dist = dist + 1;
                
                if (my_obstacles < 0) continue;
                if (visited[neigh.r][neigh.c][my_obstacles] != -1 && 
                    visited[neigh.r][neigh.c][my_obstacles] <= my_dist) continue;
                
                visited[neigh.r][neigh.c][my_obstacles] = my_dist;                
                q.push({neigh, {my_dist, my_obstacles}});                
            }
        }
        
        if (best == std::numeric_limits<int>::max()) return -1;
        return best;
    }
};

