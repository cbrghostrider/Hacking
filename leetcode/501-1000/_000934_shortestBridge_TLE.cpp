class Solution {
public:
    // Run union find, to connect island cells.
    // Each water cell remains its own "island".
    // now we have n+2 cells, where n=number of water cells.
    // let each such "cell" be a node in a graph, the 2 cells are start/end.
    // run BFS to get the answer.
    
    int R, C;
    vector<int> leaders;
    vector<int> sizes;
    int source=-1, target=-1;
    
    // leader i is connected to other leaders
    unordered_map<int, unordered_set<int>> graph;
    
    void init() {
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                int val = r*C + c;
                leaders.push_back(val);
                sizes.push_back(1);
            }
        }
    }
    
    int getIndex(int row, int col) {return (row*C + col);}
    
    int find(int index) {
        while (index != leaders[index]) {
            index = leaders[index];
        }
        return index;
    }
    
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
    
    void buildGraph(vector<vector<int>>& grid) {
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                int my_leader = find(getIndex(r, c));
                if (grid[r][c] == 1) {
                    if (source == -1) { source = my_leader; } else if (my_leader != source) { target = my_leader; }
                }
                if (r != 0)   {
                    int other_leader = find(getIndex(r-1, c)); 
                    if (other_leader != my_leader) graph[my_leader].insert(other_leader);
                }
                if (r != R-1) {
                    int other_leader = find(getIndex(r+1, c)); 
                    if (other_leader != my_leader) graph[my_leader].insert(other_leader);
                }
                if (c != 0)   {
                    int other_leader = find(getIndex(r, c-1)); 
                    if (other_leader != my_leader) graph[my_leader].insert(other_leader);
                }                
                if (c != C-1)   {
                    int other_leader = find(getIndex(r, c+1)); 
                    if (other_leader != my_leader) graph[my_leader].insert(other_leader);
                }                                
            }
        }
    }
    
    int shortestBridge(vector<vector<int>>& grid) {
        R = grid.size();
        C = grid[0].size();
        
        init();
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 0) continue;
                int my_leader = find(getIndex(r, c));
                if (r != 0 && grid[r-1][c] == 1)   {unite(my_leader, find(getIndex(r-1, c)));}
                if (r != R-1 && grid[r+1][c] == 1) {unite(my_leader, find(getIndex(r+1, c)));}
                if (c != 0 && grid[r][c-1] == 1)   {unite(my_leader, find(getIndex(r, c-1)));}
                if (c != C-1 && grid[r][c+1] == 1) {unite(my_leader, find(getIndex(r, c+1)));}                
            }
        }
        
        buildGraph(grid);
        int s=source, t=target;
        auto& ldrs = leaders;
        
        // BFS.
        // (leader, dist)
        std::queue<pair<int, int>> q;
        unordered_set<int> done;
        q.push({source, 0});
        done.insert(source);
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            if (elem.first == target) return elem.second-1;  // -1 to remove the last hop
            
            for (int neigh : graph[elem.first]) {
                if (done.find(neigh) != done.end()) continue;
                done.insert(elem.first);
                q.push({neigh, elem.second+1});
            }
        }
        return -1;  // should not get here.
    }
};
