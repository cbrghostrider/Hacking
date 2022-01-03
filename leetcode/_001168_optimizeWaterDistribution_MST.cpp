class Solution {    
public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {        
        // key_outer = from house i
        // key_inner = to house j
        // value = the cost of the pipe
        unordered_map<int, unordered_map<int, int>> pipe_costs;
        for (const auto& pipe : pipes) {
            if (pipe_costs[pipe[0]-1].find(pipe[1]-1) != pipe_costs[pipe[0]-1].end()) {
                // Parallel edge!!!
                int existing = pipe_costs[pipe[0]-1][pipe[1]-1];
                pipe_costs[pipe[0]-1][pipe[1]-1] = std::min(pipe[2], existing);
                pipe_costs[pipe[1]-1][pipe[0]-1] = std::min(pipe[2], existing);
            } else {
                pipe_costs[pipe[0]-1][pipe[1]-1] = pipe[2];
                pipe_costs[pipe[1]-1][pipe[0]-1] = pipe[2];
            }
        }
        
        // cost of node n
        unordered_map<int, int> done;
        int min_cost=0;
                
        // well cost, house index
        auto comp = [](const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
            if (lhs.first != rhs.first) return lhs.first > rhs.first;
            return lhs.second > rhs.second;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> min_heap(comp);
                
        for (int i=0; i<wells.size(); i++) {
            min_heap.push({wells[i], i});
        }
        
                
        while (!min_heap.empty()) {
            auto elem=min_heap.top(); min_heap.pop();
            int index=elem.second;
            int cost = elem.first;
            if (done.find(index) != done.end()) continue;
                        
            done[index] = std::min(wells[index], cost);
            min_cost += done[index];
            
            for (const auto& choice: pipe_costs[index]) {
                if (done.find(choice.first) != done.end()) continue;  // pipe to done house is ignored
                if (wells[choice.first] >= choice.second) {
                    min_heap.push({choice.second, choice.first});
                }
            }                        
        }
        return min_cost;
    }
};
