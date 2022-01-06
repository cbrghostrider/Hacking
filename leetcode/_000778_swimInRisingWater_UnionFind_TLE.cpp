class Solution {
    // Union Find data.
    vector<int> leaders;
    vector<int> sizes;
    vector<int> heights;
    
    int R, C;
    int source, dest;
    
    // min heap of valid heights
    priority_queue<int, vector<int>, std::greater<int>> min_heap;
    
    // Key outer: group ID (leader ID)
    // Key inner: neighbor height
    // value inner: num of neighboring "leaders" at this height
    unordered_map<int, unordered_map<int, set<int>>> group_info;
    
    // records which leaders are at which height
    unordered_map<int, unordered_set<int>> ht_to_leaders; 
    
    // finds the leader for index
    int uf_find(int index) {
        while (leaders[index] != index) {
            index = leaders[index];
        }
        return index;
    }
    
    // Union between two leaders.
    void uf_union(int leader1, int leader2) {
        leader1 = uf_find(leader1);
        leader2 = uf_find(leader2);
        if (leader1 == leader2) return;
        
        if (sizes[leader1] >= sizes[leader2]) {
            leaders[leader2] = leader1;
            sizes[leader1] += sizes[leader2];
            ht_to_leaders[heights[leader1]].erase(leader1);
            ht_to_leaders[heights[leader2]].erase(leader2);            
            heights[leader1] = std::max(heights[leader1], heights[leader2]);
            ht_to_leaders[heights[leader1]].insert(leader1);
            unify_neighbors(leader1, leader2, heights[leader1]);
        } else {
            leaders[leader1] = leader2;
            sizes[leader2] += sizes[leader1];
            ht_to_leaders[heights[leader1]].erase(leader1);
            ht_to_leaders[heights[leader2]].erase(leader2);
            heights[leader2] = std::max(heights[leader1], heights[leader2]);            
            ht_to_leaders[heights[leader2]].insert(leader2);
            unify_neighbors(leader2, leader1, heights[leader2]);
        }
    }
    
    // neighbors will be unified under leader1
    // everyone below min_height is ignored
    void unify_neighbors(int leader1, int leader2, int min_height) {
        auto& l1_neighbors = group_info[leader1];
        auto& l2_neighbors = group_info[leader2];
        
        unordered_set<int> heights;                        
        unordered_map<int, set<int>> new_neighbors;        
        for (const auto& kv : l1_neighbors) { heights.insert(kv.first); }
        for (const auto& kv : l2_neighbors) { heights.insert(kv.first); }
        
        for (int h : heights) {
            if (h <= min_height) continue;
            set<int> combo1, combo2;
            std::set_union(l1_neighbors[h].begin(), l1_neighbors[h].end(), 
                           l2_neighbors[h].begin(), l2_neighbors[h].end(), 
                           std::inserter(combo1, combo1.begin()));
            for (int n : combo1) {
                int n_leader = uf_find(n);
                combo2.insert(n_leader);
            }
            new_neighbors[h] = combo2;
        }
        
        group_info.erase(leader1);
        group_info.erase(leader2);
        group_info[leader1] = new_neighbors;
    }
    
    // converts a cell coord into an "index" number.
    int getIndex(int r, int c) {
        return ((r * C) + (c));
    }
    
    void initialize(const vector<vector<int>>& grid) {
        R=grid.size();
        C=grid[0].size();
        source = getIndex(0, 0);
        dest = getIndex(R-1, C-1);
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                int index = getIndex(r, c);
                leaders.push_back(index);
                sizes.push_back(1);
                heights.push_back(grid[r][c]);
                ht_to_leaders[grid[r][c]].insert(index);
            }
        }
        
        // Unify neighboring groups at same height
        // and store info about neighboring groups at greater height
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                int my_index = getIndex(r, c);
                int my_leader = uf_find(my_index);
                
                vector<pair<int, int>> neighbors = {{r-1, c}, {r+1, c}, {r, c-1}, {r, c+1}};
                for (auto& neigh : neighbors) {
                    int rn = neigh.first, cn=neigh.second;
                    if (rn < 0 || rn >= R || cn < 0 || cn >= C) continue;
                    int neigh_index = getIndex(rn, cn);
                    int neigh_leader = uf_find(neigh_index);
                    if (grid[r][c] < grid[rn][cn]) {
                        group_info[my_leader][grid[rn][cn]].insert(neigh_leader);
                    } else if (grid[r][c] == grid[rn][cn]) {                        
                        uf_union(my_leader, neigh_leader);
                    }
                }
            }
        }
        
        for (const auto& kv : ht_to_leaders) {
            min_heap.push(kv.first);
        }
    }
    
public:
    int swimInWater(vector<vector<int>>& grid) {
        initialize(grid);
        if (uf_find(source) == uf_find(dest)) return grid[0][0];  // already connected at time 0
        
        int curr_time=min_heap.top(); min_heap.pop();
        
        while(!min_heap.empty()) {
            int new_time = min_heap.top(); min_heap.pop();
            
            // everything from curr_time to new_time in height should get connected if they are adjacent
            auto process = ht_to_leaders[curr_time];
            for (int ld : process) {
                for (int neigh : group_info[ld][new_time]) {
                    uf_union(ld, neigh);
                }
            }
            for (int p : process) {
                int ld = uf_find(p);
                if (heights[ld] != new_time) {
                    heights[ld] = new_time;                    
                    ht_to_leaders[heights[ld]].insert(ld);
                }
                ht_to_leaders.erase(curr_time);
            }
            
            if (uf_find(source) == uf_find(dest)) return new_time;
            curr_time = new_time;
        }
        
        return -1;  // should not get here
    }
};
