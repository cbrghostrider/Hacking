struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {
        return (r == rhs.r && c == rhs.c);
    }
    bool operator!=(const Coord& rhs) const {
        return !(*this == rhs);
    }
};
template<>
struct hash<Coord> {
size_t operator()(const Coord& key) const {
    return ((key.r << 16) | (key.c));
}
};
struct Info {
    Coord me;    // these are my coordinates
    Coord from;  // arrived at me via here
};
class Solution {
    // Choose any traversal, BFS or DFS, doesn't matter.
    //
    // The key observation is this:
    // For no cycle, at any point in the traversal (except the beginning), 
    // I should have EXACTLY 1 VISITED neighbor of the SAME value.
    // In the beginning I have 0 visited neighbors of the same value.
    //
    // Further once there is a cycle, it is by default at least 4 long.
    // (as per the above definition).
    
    int R, C;
    unordered_set<Coord> visited;
    
    // returns true if it detects a cycle during this traversal.
    bool bfs(const vector<vector<char>>& grid, Coord coord) {
        const char letter = grid[coord.r][coord.c];
        std::queue<Info> q;
        q.push({coord, coord});
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            Coord crd = elem.me;
            
            vector<Coord> neighs = {
                {crd.r-1, crd.c}, {crd.r+1, crd.c}, {crd.r, crd.c-1}, {crd.r, crd.c+1}
            };
            for (const Coord& neigh : neighs) {
                if (neigh.r < 0 || neigh.r >= R || neigh.c < 0 || neigh.c >= C) continue;
                if (grid[neigh.r][neigh.c] != letter) continue;
                if (neigh == elem.from) continue;
                if (visited.find(neigh) != visited.end()) {return true;}
                visited.insert(neigh);
                q.push({neigh, crd});
            }            
        }
        return false;
    }
    
public:
    // O(R*C) time, O(R*C) space.
    bool containsCycle(vector<vector<char>>& grid) {
        R=grid.size();
        C=grid[0].size();        
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (visited.find({r, c}) != visited.end()) continue;
                visited.insert({r, c});
                if (bfs(grid, {r, c})) return true;
            }
        }
        return false;
    }
};
