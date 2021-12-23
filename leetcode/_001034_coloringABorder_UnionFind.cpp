class Solution {
    vector<int> leaders;
    vector<int> sizes;
    int R, C;
    
    int getIndex(int r, int c) {return (r*C + c);}
    
    void uf_init() {
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                leaders.push_back(getIndex(r, c));
                sizes.push_back(1);
            }
        }
    }
    
    int uf_find(int index) {
        while (index != leaders[index]) {
            index = leaders[index];
        }
        return index;
    }
    
    void uf_union(int leader1, int leader2) {
        if (leader1 == leader2) return;
        if (sizes[leader1] < sizes[leader2]) {
            leaders[leader1] = leader2;
            sizes[leader2] += sizes[leader1];
        } else {
            leaders[leader2] = leader1;
            sizes[leader1] += sizes[leader2];            
        }
    }
    
    bool isOtherComp(int check_leader, int r, int c) {
        if (r < 0 || r >= R || c < 0 || c >= C) return true;
        int my_leader = uf_find(getIndex(r, c));
        return (my_leader != check_leader);
    }
    
    // is this in the boundary set for leader
    bool isBoundary(int leader, int r, int c) {
        int my_leader = uf_find(getIndex(r, c));
        if (my_leader != leader) return false;
        if (isOtherComp(my_leader, r-1, c)) return true;
        if (isOtherComp(my_leader, r+1, c)) return true;
        if (isOtherComp(my_leader, r, c-1)) return true;
        if (isOtherComp(my_leader, r, c+1)) return true;
        return false;
    }
    
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        R=grid.size(); C=grid[0].size();
        
        uf_init();
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                int my_index = getIndex(r, c);
                int my_leader = uf_find(my_index);
                int my_color = grid[r][c];
                
                if (r != 0   && grid[r-1][c] == my_color) {
                    uf_union(my_leader, uf_find(getIndex(r-1, c)));
                }
                if (r != R-1 && grid[r+1][c] == my_color) {
                    uf_union(my_leader, uf_find(getIndex(r+1, c)));
                }
                if (c != 0   && grid[r][c-1] == my_color) {
                    uf_union(my_leader, uf_find(getIndex(r, c-1)));
                }
                if (c != C-1 && grid[r][c+1] == my_color) {
                    uf_union(my_leader, uf_find(getIndex(r, c+1)));
                }
            }
        }
        
        int check_leader = uf_find(getIndex(row, col));
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (isBoundary(check_leader, r, c)) {
                    grid[r][c] = color;
                }
            }
        }
        return grid;
    }
};
