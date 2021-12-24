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
    
    int bfs(vector<vector<int>>& grid, int r, int c) {
        std::queue<Info> q, processed;
        q.push({{r, c}, 0});
        grid[r][c] = 2;  // visited
        
        int ans=0;
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            Coord crd = elem.crd;
            processed.push(elem);
            
            if (crd.r != 0 && grid[crd.r-1][crd.c] != 2) {
                if (grid[crd.r-1][crd.c] == 1) { ans = elem.dist+1; break; }
                grid[crd.r-1][crd.c] = 2;
                q.push({{crd.r-1, crd.c}, elem.dist+1});
            }
            if (crd.r != R-1 && grid[crd.r+1][crd.c] != 2) {
                if (grid[crd.r+1][crd.c] == 1) { ans = elem.dist+1; break; }
                grid[crd.r+1][crd.c] = 2;
                q.push({{crd.r+1, crd.c}, elem.dist+1});
            }
            if (crd.c != 0 && grid[crd.r][crd.c-1] != 2) {
                if (grid[crd.r][crd.c-1] == 1) { ans = elem.dist+1; break; }
                grid[crd.r][crd.c-1] = 2;
                q.push({{crd.r, crd.c-1}, elem.dist+1});
            }
            if (crd.c != C-1 && grid[crd.r][crd.c+1] != 2) {
                if (grid[crd.r][crd.c+1] == 1) { ans = elem.dist+1; break; }
                grid[crd.r][crd.c+1] = 2;
                q.push({{crd.r, crd.c+1}, elem.dist+1});
            }
        }
        while (!processed.empty()) {
            auto elem=processed.front(); processed.pop();
            q.push(elem);
        }
        while (!q.empty()) {
            auto elem=q.front(); q.pop();
            grid[elem.crd.r][elem.crd.c] = 0;  // unvisit marked but unprocessed nodes
        }
        return ans;
    }
public:
    // O(R*R*C*C) time.
    // This is because each BFS takes O(RC) time, and we reset visited state for each BFS.
    int maxDistance(vector<vector<int>>& grid) {
        R=grid.size();
        C=grid[0].size();
        
        int best=0;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] != 0) continue;
                int my_max = bfs(grid, r, c);
                best = std::max(best, my_max);
            }
        }
        return best ? best : -1;
    }
};
