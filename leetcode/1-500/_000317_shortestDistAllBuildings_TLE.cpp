class Solution {
    struct Coord {
        int r=0; 
        int c=0;
    };
    int R, C;
    int num_houses=0;
    
    vector<vector<int>> dist;      // total dist to all houses
    vector<vector<int>> touched;   // how many houses could visit me
    
    // O(R*C) time.
    void bfs(const vector<vector<int>>& grid, int hr, int hc) {
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        
        queue<pair<Coord, int>> q;
        q.push({{hr, hc}, 0});
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            Coord my_crd = elem.first;
            int my_dist = elem.second;
            if (grid[my_crd.r][my_crd.c] == 0) {
                dist[my_crd.r][my_crd.c] += my_dist;
                touched[my_crd.r][my_crd.c] += 1;
            }
            
            vector<Coord> neighs = {
                {my_crd.r-1, my_crd.c}, {my_crd.r, my_crd.c-1}, 
                {my_crd.r+1, my_crd.c}, {my_crd.r, my_crd.c+1}
            };
            
            for (const Coord& neigh : neighs) {
                if (neigh.r < 0 || neigh.c < 0 || neigh.r >= R || neigh.c >= C) continue;
                if (visited[neigh.r][neigh.c] == true) continue;
                if (grid[neigh.r][neigh.c] != 0) continue;
                visited[neigh.r][neigh.c] = true;
                q.push({neigh, my_dist+1});
            }
        }        
    }
    
public:
    // O(R*R*C*C) time, O(R*C) space.
    int shortestDistance(vector<vector<int>>& grid) {
        R = grid.size();
        C = grid[0].size();
        dist = touched = vector<vector<int>>(R, vector<int>(C, 0));
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 1) {
                    bfs(grid, r, c);
                    num_houses++;
                }
            }
        }
        
        int ans = std::numeric_limits<int>::max();
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] != 0 || touched[r][c] != num_houses) continue;
                ans = std::min(ans, dist[r][c]);
            }
        }
        
        return (ans == std::numeric_limits<int>::max() ? -1 : ans);
    }
};
