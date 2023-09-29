class Solution {
    int R, C;
    
    struct Coord {
        int row=0;
        int col=0;
    };
    
    bool isEmpty(vector<vector<int>>& rooms, int r, int c) {
        return (rooms[r][c] != 0 && rooms[r][c] != -1);
    }
    
    void bfs(vector<vector<int>>& rooms, int g_row, int g_col) {
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        
        // (coord, dist from curr gate)
        std::queue<pair<Coord, int>> q;
        visited[g_row][g_col] = true;
        q.push({{g_row, g_col}, 0});
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            int r=elem.first.row, c=elem.first.col, dist=elem.second;
            if (rooms[r][c] >= dist) {rooms[r][c] = dist;}
            
            if (r != 0   && isEmpty(rooms, r-1, c) && visited[r-1][c] == false) {
                visited[r-1][c] = true;
                q.push({{r-1, c}, dist+1});
            }
            if (r != R-1 && isEmpty(rooms, r+1, c) && visited[r+1][c] == false) {
                visited[r+1][c] = true;
                q.push({{r+1, c}, dist+1});                
            }
            if (c != 0   && isEmpty(rooms, r, c-1) && visited[r][c-1] == false) {
                visited[r][c-1] = true;
                q.push({{r, c-1}, dist+1});                
            }
            if (c != C-1 && isEmpty(rooms, r, c+1) && visited[r][c+1] == false) {
                visited[r][c+1] = true;
                q.push({{r, c+1}, dist+1});                                
            }
        }
    }
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        R=rooms.size();
        C=rooms[0].size();
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (rooms[r][c] == 0) {
                    bfs(rooms, r, c);
                }
            }
        }
    }
};
