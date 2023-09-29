class Solution {
    struct Coord {
        int r=0;
        int c=0;
        bool operator==(const Coord& rhs) const {
            return (r == rhs.r && c == rhs.c);
        }
    };
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        const int R=grid.size();
        const int C=grid[0].size();
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 1) {grid[r][c] = -1;}
            }
        }
        if (grid[0][0] == -1) return -1;
        if (grid[R-1][C-1] == -1) return -1;
        
        std::queue<Coord> q;
        q.push({0, 0});
        grid[0][0] = 1;
        Coord target = {R-1, C-1};
        
        while (!q.empty()) {
            auto elem=q.front(); q.pop();
            if (elem == target) {
                return grid[R-1][C-1];
            }
            
            vector<Coord> neighs = {
                {elem.r-1, elem.c}, {elem.r, elem.c-1}, 
                {elem.r+1, elem.c}, {elem.r, elem.c+1},
                {elem.r-1, elem.c-1}, {elem.r+1, elem.c-1},
                {elem.r-1, elem.c+1}, {elem.r+1, elem.c+1}                
            };
            for (const Coord& n : neighs) {
                if (n.r<0 || n.r>=R || n.c<0 || n.c>=C) continue;
                if (grid[n.r][n.c] != 0) continue;
                grid[n.r][n.c] = grid[elem.r][elem.c] + 1;
                q.push({n.r, n.c});
            }
        }
        return -1;
    }
};
