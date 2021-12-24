struct Coord {
    int r=0;
    int c=0;
};
struct Info {
    Coord crd;
    int dist=0;
};

class Solution {
    int R, C;
    
    void bfs(vector<vector<int>>& grid, std::queue<Info>& q) {
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            Coord crd = elem.crd;
            int dist = elem.dist;
            
            if (crd.r != 0 && 
                (grid[crd.r-1][crd.c] > dist + 1 || grid[crd.r-1][crd.c] == 0)) {                
                grid[crd.r-1][crd.c] = dist + 1;
                q.push({{crd.r-1, crd.c}, elem.dist+1});
            }
            if (crd.r != R-1 && 
               (grid[crd.r+1][crd.c] > dist + 1 || grid[crd.r+1][crd.c] == 0)) {
                grid[crd.r+1][crd.c] = dist+1;
                q.push({{crd.r+1, crd.c}, elem.dist+1});
            }
            if (crd.c != 0 && 
               (grid[crd.r][crd.c-1] > dist + 1 || grid[crd.r][crd.c-1] == 0)) {
                grid[crd.r][crd.c-1] = dist+1;
                q.push({{crd.r, crd.c-1}, elem.dist+1});
            }
            if (crd.c != C-1 && 
               (grid[crd.r][crd.c+1] > dist + 1 || grid[crd.r][crd.c+1] == 0)) {
                grid[crd.r][crd.c+1] = dist+1;
                q.push({{crd.r, crd.c+1}, elem.dist+1});
            }
        }
        return;
    }
public:
    // O(R*C) time.
    // We do simultaneous BFS starting from all the land cells neighbors at once.
    int maxDistance(vector<vector<int>>& grid) {
        R=grid.size();
        C=grid[0].size();
        
        std::queue<Info> q;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 0 || grid[r][c] == 2) continue;
                if (r != 0 && grid[r-1][c] == 0)   {
                    q.push({{r-1, c}, 2});
                    grid[r-1][c] = 2;
                }
                if (r != R-1 && grid[r+1][c] == 0) {
                    q.push({{r+1, c}, 2});
                    grid[r+1][c] = 2;
                }
                if (c != 0 && grid[r][c-1] == 0)   {
                    q.push({{r, c-1}, 2});
                    grid[r][c-1] = 2;
                }
                if (c != C-1 && grid[r][c+1] == 0) {
                    q.push({{r, c+1}, 2});
                    grid[r][c+1] = 2;
                }                
            }
        }
        
        bfs(grid, q);
        
        int best=0;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] >= 2) {
                    best = std::max(best, grid[r][c]);
                }
            }
        }
        return best-1;
    }
};
