class Solution {
    // Each "cell" can be considered to be 2 "halves"
    // Let's call them "alpha" and "beta"
    // cell == ' ', doesn't matter
    // cell == '/' "alpha" is left/top half, "beta" is right/bottom half
    // cell == '\' "alpha" is left/bottom half, "beta" is right/top half
    // 
    // For union find, initially start with 2*R*C leaders
    // All the alpha leaders will be stored in the first R*C vals
    // All the beta leaders will be stored in the second R*C vals
    
    enum Dir {UP=0, DOWN, LEFT, RIGHT};
    
    vector<int> leaders;
    vector<int> sizes;
    int R, C;
    
    int uf_find(int index) {
        while (index != leaders[index]) {
            index = leaders[index];
        }
        return index;
    }
    
    void uf_union(int leader1, int leader2) {
        if (leader1 == leader2) return;
        if (sizes[leader1] >= sizes[leader2]) {
            leaders[leader2] = leader1;
            sizes[leader1] += sizes[leader2];
        } else {
            leaders[leader1] = leader2;
            sizes[leader2] += sizes[leader1];            
        }
    }
    
    void init() {
        for (int i=0; i<2*R*C; i++) {
            leaders.push_back(i);
            sizes.push_back(1);
        }
    }
    
    int alphaIndex(int r, int c) {
        return (r * C + c);
    }
    
    int betaIndex(int r, int c) {
        return (R*C + alphaIndex(r, c));
    }
    
    pair<int, int> neighIndices(int my_r, int my_c, Dir dir) {
        int dr = dir == UP   ? -1 : (dir == DOWN  ? 1 : 0);
        int dc = dir == LEFT ? -1 : (dir == RIGHT ? 1 : 0);
        int neigh_ai = alphaIndex(my_r+dr, my_c+dc);
        int neigh_bi = betaIndex(my_r+dr, my_c+dc);
        return {neigh_ai, neigh_bi};
    }
    
    // ai, bi are alpha beta indices
    // my/n refer to my cell or neigh cell
    // direction refers to the direction of unification
    // me/neigh are cell contents
    void unify(const vector<string>& grid, int my_r, int my_c, char me, Dir dir) {
        int aIndex = alphaIndex(my_r, my_c);
        int bIndex = betaIndex(my_r, my_c);
        
        auto ninds = neighIndices(my_r, my_c, dir);
        int neigh_ai = ninds.first;
        int neigh_bi = ninds.second;
        
        if (me == ' ' || me == '/') {
            // Unify my alpha with either alpha OR beta on my top AND my left
            if (my_r > 0 && dir == UP) { 
                char neigh = grid[my_r-1][my_c];
                int chosen = neigh == '/' || neigh == ' ' ? neigh_bi : neigh_ai;
                uf_union(uf_find(aIndex), uf_find(chosen));
            }
            if (my_c > 0 && dir == LEFT) {
                char neigh = grid[my_r][my_c-1];
                int chosen = neigh_bi;
                uf_union(uf_find(aIndex), uf_find(chosen));
            }
            
            // Unify my beta with either alpha OR beta on my bottom AND my right
            if (my_r < R-1 && dir == DOWN) { 
                char neigh = grid[my_r+1][my_c];
                int chosen = neigh == '/' || neigh == ' ' ? neigh_ai : neigh_bi;
                uf_union(uf_find(bIndex), uf_find(chosen));
            }
            if (my_c < C-1 && dir == RIGHT) {
                char neigh = grid[my_r][my_c+1];
                int chosen = neigh_ai;
                uf_union(uf_find(bIndex), uf_find(chosen));
            }            
        }
        if (me == ' ' || me == '\\') {
            // Unify my beta with either alpha OR beta on my top AND my right
            if (my_r > 0 && dir == UP) {
                char neigh = grid[my_r-1][my_c];
                int chosen = neigh == '/' || neigh == ' ' ? neigh_bi : neigh_ai;
                uf_union(uf_find(bIndex), uf_find(chosen));
            }
            if (my_c < C-1 && dir == RIGHT) {
                char neigh = grid[my_r][my_c+1];
                int chosen = neigh_ai;
                uf_union(uf_find(bIndex), uf_find(chosen));
            }
            
            // Unify my alpha with either alpha OR beta on my bottom AND my left
            if (my_r < R-1 && dir == DOWN) {
                char neigh = grid[my_r+1][my_c];
                int chosen = neigh == '/' || neigh == ' '? neigh_ai : neigh_bi;
                uf_union(uf_find(aIndex), uf_find(chosen));
            }
            if (my_c > 0 && dir == LEFT) {
                char neigh = grid[my_r][my_c-1];
                int chosen = neigh_bi;
                uf_union(uf_find(aIndex), uf_find(chosen));
            }            
        }
    }
    
    // unifies regions
    void process(const vector<string>& grid) {
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {                            
                if (grid[r][c] == ' ') {
                    uf_union(uf_find(alphaIndex(r, c)), uf_find(betaIndex(r, c)));
                }
                
                unify(grid, r, c, grid[r][c], UP);
                unify(grid, r, c, grid[r][c], DOWN);
                unify(grid, r, c, grid[r][c], LEFT);
                unify(grid, r, c, grid[r][c], RIGHT);                
            }
        }
    }
    
    int countRegions() {
        
        int count=0;
        for (int i=0; i<leaders.size(); i++) {
            if (i == leaders[i]) {count++;}
        }
        return count;
    }
    
public:
    int regionsBySlashes(vector<string>& grid) {
        R = grid.size();
        C = grid[0].size();
        
        init();
        process(grid);
        int ans = countRegions();
        return ans;
    }
};
