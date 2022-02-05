class Solution {
    struct Info {
        int cost=0;
        int time_left=0;
        int node=0;
    };
    vector<int> fees;
    
    // key_outer: from node
    // key_inner: to node
    // value: min cost of all such direct roads
    unordered_map<int, unordered_map<int, int>> adj_list;
    
    void addRoad(int from, int to, int cost) {
        if (adj_list[from].find(to) == adj_list[from].end()) {
            adj_list[from][to] = cost;
        } else {
            adj_list[from][to] = std::min(adj_list[from][to], cost);
        }
    }
    
    void populate(const vector<vector<int>>& edges) {
        for (const vector<int>& edge : edges) {            
            addRoad(edge[0], edge[1], edge[2]);
            addRoad(edge[1], edge[0], edge[2]);
        }
    }   
    
    function<bool(const Info&, const Info&)> comp = [](const Info& lhs, const Info& rhs) -> bool {
        if (lhs.time_left != rhs.time_left) {return lhs.time_left < rhs.time_left;}
        if (lhs.cost != rhs.cost) {return lhs.cost > rhs.cost;}        
        return lhs.node > rhs.node;
    };
    
    using MinHeap = priority_queue<Info, vector<Info>, decltype(comp)>;
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        fees = passingFees;
        int n = fees.size();
        populate(edges);
        
        int best = std::numeric_limits<int>::max();
        MinHeap min_heap(comp);
        
        // visited key:node with (time_left, cost so far)
        // the idea is that if you visit this node AGAIN with both 
        //       time_left < recorded AND
        //       cost > recorded
        // then we can prune that path
        unordered_map<int, pair<int, int>> visited;
        
        visited[0] = {maxTime, fees[0]};
        min_heap.push({fees[0], maxTime, 0});
        
        while (!min_heap.empty()) {
            auto elem = min_heap.top(); min_heap.pop();
            if (elem.node == n-1) {  // destination
                best = std::min(best, elem.cost);
                continue;
            }
            
            for (const auto& kv : adj_list[elem.node]) {
                int neigh = kv.first;
                int time = kv.second;
                int my_cost = elem.cost + fees[neigh];
                int my_time = elem.time_left - time;
                
                // 3 types of pruning.

                // Don't have enough time to traverse road!
                if (time > elem.time_left) continue;                

                // Already incurred too much of a cost, and something better cost made it through already.
                if (my_cost > best) continue;

                // See note above the map declaration.
                if (visited.find(neigh) != visited.end()) {
                    auto record = visited[neigh];
                    if (record.first >= my_time && record.second <= my_cost) {
                        continue;
                    }
                }
                visited[neigh] = {my_time, my_cost};
                    
                Info info = {my_cost, my_time, neigh};
                min_heap.push(info);
            }
        }
        
        return best == std::numeric_limits<int>::max() ? -1 : best;
    }
};

