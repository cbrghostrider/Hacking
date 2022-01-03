// 
// Run through the arrays from 0 to n-1
// At each step, we will maintain bookkeeping information on the choices made so far.
// 
// Bookkeeping:
// House i: Did we choose to build well, or connect with pipe?
// If we chose to connect with pipe, which was the house index (lowest cost pipe) we chose?
//
// Now consider at some intermediate point in the algorithm, we have processed i-1 houses.
// For the ith house, we have the following choices:
// 
// 1. Build a well here.
//         If we choose to build a well, then we can "re-wire" previous choices made.
//         Look at bookkeeping info. If a prev house connected to our house is now
//         cheaper to connect with us via a pipe: pipe[i, k], then connect that instead
//         Note that (well[k] or pipe[k, q]) in prev house was the prev cost we compared
//         where k is prev house, q is the pipe from that house to the house it connected with
//         if piping was chosen for house k, else just well[k].
// 2. Choose to connect with pipe.
//         Choose lowest cost pipe to existing houses. Also rewire if needed
// 
// Best choice is one of the two above.
// Make sure to update the actual bookkeeping info *ONLY* as per the best choice made
//
class Solution {    
    // this is savings taking into account re-wiring    
    // Assumes new house now has water (either via well, or pipe)
    // If the new house was piped from somewhere, the index of the piped house
    // is provided, else it is -1
    // execute says whether we should update the actual bookkeeping info or not
    /*
    int evaluateRewiring(int new_index, int piped=-1, bool execute=false) {
        int delta=0; auto&ppp = pipe_costs;
        for (const auto& pcs : pipe_costs[new_index]) {
            if (done.find(pcs.first) == done.end()) continue;  // pipe to future house is ignored...
            if (pcs.first == piped) continue;  // ignore this particular house
            
            int prev_index = pcs.first;
            int cost_prev = 
                choices[prev_index].chose_well 
                    ? well_costs[prev_index] 
                    : pipe_costs[prev_index][choices[prev_index].connector];
            int cost_new = pcs.second;
            if (cost_prev > cost_new) {
                delta += cost_prev - cost_new;  // savings if we switched the choice
                if (execute) {  // we are being asked to do the actual re-wiring
                    choices[prev_index].chose_well = false;
                    choices[prev_index].connector = new_index;
                }
            }
        }
        return delta;
    }
    
    // For a house "new_index", find the cheapest pipe connecting me
    // ONLY CONSIDER houses before my index though.
    int getCheapestPipeIndex(int new_index) {
        int index=-1;
        int cost = std::numeric_limits<int>::max();
        for (const auto& pcs : pipe_costs[new_index]) {
            if (done.find(pcs.first) == done.end()) continue;  // pipe to future house is ignored...
            if (pcs.second < cost) {
                index = pcs.first;
                cost = pcs.second;
            }
        }
        return index;
    }
    */
    
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
