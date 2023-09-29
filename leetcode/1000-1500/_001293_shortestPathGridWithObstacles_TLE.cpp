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

// key: number of obstacles overcome
// value: min distance for key number of obstacles overcome
using Info = unordered_map<int, int>;

class Solution {
    // [r][c][kp]
    // kp <- 0..k
    // value: the number of steps to get to this cell, with exactly kp obstacles overcome
    vector<vector<vector<int>>> visited;
    
    void merge(const Coord& crd, const Info& info) {
        int r=crd.r, c=crd.c;
        for (const auto& kv : info) {
            int key = kv.first;
            int dist = kv.second;
            if (visited[r][c][key] == -1 || visited[r][c][key] > dist) {
                visited[r][c][key] = dist;
            }
        }
    }
    
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        const int R=grid.size();
        const int C=grid[0].size();
        visited = vector<vector<vector<int>>>(R, vector<vector<int>>(C, vector<int>(k+1, -1)));
        
        queue<pair<Coord, Info>> q;
        q.push({{0, 0}, {{/*key=*/0, /*path len*/0}}});
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            Coord crd = elem.first;
            const Info& info = elem.second;            
            merge(crd, info);
            
            vector<Coord> neighs = {
                {crd.r-1, crd.c}, {crd.r+1, crd.c},
                {crd.r, crd.c-1}, {crd.r, crd.c+1}
            };
            
            for (const Coord& neigh : neighs) {
                if (neigh.r < 0 || neigh.r >= R || neigh.c < 0 || neigh.c >= C) continue;
                Info my_info;
                int add_val = grid[neigh.r][neigh.c];                
                
                // Only pursue those which are lesser distance for same k.
                for (const auto& kv : info) {
                    int my_k = kv.first + add_val;
                    int my_dist = kv.second+1;
                    
                    // too many obstacle removals
                    if (my_k > k) continue;  
                    
                    // A better path exists already for these many (or fewer) obstacle removals for this cell.
                    bool skip_iter=false;
                    for (int ki=my_k; ki>=0; ki--) {
                        if (visited[neigh.r][neigh.c][ki] != -1 && 
                            visited[neigh.r][neigh.c][ki] <= my_dist) {
                            skip_iter = true;
                            break;
                        }                        
                    }
                    if (skip_iter) continue;
                    
                    my_info[my_k] = my_dist;
                }
                
                if (!my_info.empty()) {
                    q.push({neigh, my_info});
                }
            }
        }
        
        int best=std::numeric_limits<int>::max();
        for (int ki=0; ki<=k; ki++) {
            if (visited[R-1][C-1][ki] != -1) {
                best = std::min(best, visited[R-1][C-1][ki]);
            }
        }
        
        if (best == std::numeric_limits<int>::max()) return -1;
        return best;
    }
};
