class Solution {
    vector<vector<int>> graph;
    vector<int> leaders;
    vector<int> sizes;
    
    unordered_set<int> ends;
    unordered_set<int> done;
    
    int leader_a=-1, leader_b=-1;
    
    void uf_init() {
        for (int i=0; i<graph.size(); i++) {
            leaders.push_back(i);
            sizes.push_back(1);
        }
    }
    
    // finds leader for index
    int uf_find(int index) {
        while (index != leaders[index]) {
            index = leaders[index];
        }
        return index;
    }
    
    // unites two groups
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
    
    // Runs one pass over the graph, trying to perform bipartite matching.
    // returns whether we need to continue or not running this algorithm
    // sets is_bipartite to true/false if needed (or leaves unchanged)
    bool runBipartite(bool& is_bipartite) {
        bool found = false;
        for (int i=0; i<graph.size(); i++) {
            if (graph[i].size() == 0) {
                if (leader_a != -1) {
                    uf_union(i, uf_find(leader_a));
                    done.insert(i);
                }
                continue;
            }
            if (done.find(i) != done.end()) continue;
            
            leader_a = uf_find(i);
            leader_b = uf_find(graph[i][0]);
            for (int e : graph[i]) {
                ends.insert(e);
            }
            done.insert(i);
            found = true;
            break;
        }
        
        if (!found) return false;
        
        bool handle_a = false;  // currently handling group b
        
        while (!ends.empty()) {
            unordered_set<int> new_ends;
            int leader_other = handle_a ? uf_find(leader_b) : uf_find(leader_a);
            int leader_mine = handle_a ? uf_find(leader_a) : uf_find(leader_b);
            for (int e : ends) {
                if (uf_find(e) == leader_other) {
                    is_bipartite = false;
                    return false;
                }
                if (done.find(e) != done.end()) continue;
                                
                done.insert(e);
                uf_union(leader_mine, uf_find(e));
                for (int ne : graph[e]) {
                    if (uf_find(ne) == uf_find(e)) {
                        is_bipartite = false;
                        return false;
                    }
                    if (done.find(ne) != done.end()) continue;
                    new_ends.insert(ne);
                }
            }
            ends = new_ends;
            handle_a = !handle_a;
        }
        is_bipartite = true;
        return true;
    }
    
public:
    // Not the most elegant of algorithms, 
    // it is a bit ad-hoc.
    // But it works fine and is functionally correct.
    // Also apparently really fast, which surprised me!
    bool isBipartite(vector<vector<int>>& g) {
        graph = g;
        uf_init();
        
        bool has_edges=false;
        for (const auto& v : g) {
            if (!v.empty()) {has_edges = true; break;}
        }
        if (!has_edges) return true;
    
        bool is_bipartite = false;
        while (runBipartite(is_bipartite)) {
            ;  // keep running until no change
        }
        
        return is_bipartite;
        
        int count=0;
        for (int i=0; i<leaders.size(); i++) {
            if (leaders[i] == i) count++;
        }
        return count==2;  // bipartite graph should have exactly 2 groups
    }
};
