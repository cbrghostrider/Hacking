class Solution {
    vector<int> leaders;
    vector<int> sizes;
    int R=0, C=0;
    
    int sig(int r, int c) {
        return (r*C + c);
    }
    
    // finds the leader: O(log RC) time.
    int find(int r, int c) {
        int ind = sig(r, c);
        while (leaders[ind] != ind) {
            ind = leaders[ind];
        }
        return ind;
    }
    
    // O(1) time.
    void unite(int leader1, int leader2) {
        if (leader1 == leader2) return;
        if (sizes[leader1] < sizes[leader2]) {
            leaders[leader1] = leader2;
            sizes[leader2] += sizes[leader1];
        } else {
            leaders[leader2] = leader1;
            sizes[leader1] += sizes[leader2];
        }
    }
    
    string getHash(const vector<pair<int, int>>& coords) {
        if (coords.size() == 1) return "SINGLE";
        pair<int, int> last = coords[0];
        string sig;
        for (int i=1; i<coords.size(); i++) {
            int delta_r = coords[i].first - last.first;
            int delta_c = coords[i].second - last.second;
            sig += std::to_string(delta_r) + "," + std::to_string(delta_c);
            last = coords[i];
        }
        return sig;
    }
    
public:
    // O(RC) space, O(RC log RC) time.
    int numDistinctIslands(vector<vector<int>>& grid) {
        R=grid.size();
        C=grid[0].size();
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                int ind = sig(r, c);
                leaders.push_back(ind);
                sizes.push_back(1);
            }
        }
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 0) continue;
                int leader = find(r, c);
                if (r != 0   && grid[r-1][c] == 1) { 
                    unite(leader, find(r-1, c)); 
                }
                if (r != R-1 && grid[r+1][c] == 1) { 
                    unite(leader, find(r+1, c)); 
                }
                if (c != 0   && grid[r][c-1] == 1) { 
                    unite(leader, find(r, c-1)); 
                }
                if (c != C-1 && grid[r][c+1] == 1) { 
                    unite(leader, find(r, c+1)); 
                }
            }
        }
        
        // each leader mapped to its island cell coordinates in order of row, col major
        unordered_map<int, vector<pair<int, int>>> island_coords;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 0) continue;
                int leader = find(r, c);
                island_coords[leader].push_back({r, c});
            }
        }

        // The idea is that the same "geometric layout" under translation will retain the deltas between coords.         
        unordered_set<string> sigs;
        for (const auto& kv : island_coords) {
            sigs.insert(getHash(kv.second));
        }
        return sigs.size();
    }
};
