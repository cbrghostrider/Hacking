class Solution {
    int R, C;
    vector<int> leaders;
    vector<int> sizes;
    
    int getIndex(int r, int c) {
        return (r*C + c);
    }
    
    // O(1) time.
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
    
    // O(log n) time.
    int uf_find(int index) {
        while (index != leaders[index]) {
            index = leaders[index];
        }
        return index;
    }
    
public:
    // O(R*C log R*C) time, O(R*C) space.
    int largestIsland(vector<vector<int>>& grid) {
        R = grid.size();
        C = grid[0].size();
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                leaders.push_back(getIndex(r, c));
                sizes.push_back(1);
            }
        }
        
        // Mark the islands in union find.
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 0) continue;
                int leader = uf_find(getIndex(r, c));
                
                vector<pair<int, int>> neighs = {
                    {r-1, c}, {r+1, c}, {r, c-1}, {r, c+1}
                };
                
                for (const auto& neigh : neighs) {
                    if (neigh.first < 0 || neigh.second < 0 || 
                        neigh.first >= R || neigh.second >= C) {continue;}
                    if (grid[neigh.first][neigh.second] == 0) continue;
                    
                    int leader_n = uf_find(getIndex(neigh.first, neigh.second));
                    uf_union(leader, leader_n);
                }
            }
        }
        
        int ans=0;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 1) {
                    int leader = uf_find(getIndex(r, c));
                    ans = std::max(ans, sizes[leader]);
                    continue;
                }
                
                vector<pair<int, int>> neighs = {
                    {r-1, c}, {r+1, c}, {r, c-1}, {r, c+1}
                };
                int sz=1;  // this 0 was turned to a 1
                unordered_set<int> merged;
                
                for (const auto& neigh : neighs) {
                    if (neigh.first < 0 || neigh.second < 0 || 
                        neigh.first >= R || neigh.second >= C) {continue;}
                    if (grid[neigh.first][neigh.second] == 0) continue;
                    
                    int leader = uf_find(getIndex(neigh.first, neigh.second));
                    if (merged.find(leader) != merged.end()) continue;
                    
                    merged.insert(leader);
                    sz += sizes[leader];
                }
                
                ans = std::max(ans, sz);
            }
        }
        
        return ans;
    }
};
