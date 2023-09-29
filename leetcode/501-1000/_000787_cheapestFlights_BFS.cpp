class Solution {
    struct Info {
        int city=0;  
        int cost=0;  // sum of cost so far
        int hop=0;   // how many stops so far
    };
    
    // city x -> {city y, cost z}  // flights from city x to other cities, and their costs
    unordered_map<int, unordered_map<int, int>> graph;
    
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        
        for (const auto& flight : flights) {
            graph[flight[0]][flight[1]] = flight[2];
        }

        // (n, cost): so far, best way to get from src to n, is cost
        unordered_map<int, int> best_way;
        
        queue<Info> q;
        q.push({src, 0, -1});        
        
        int best=std::numeric_limits<int>::max();
        while (!q.empty()) {
            auto elem=q.front(); q.pop();
            if (elem.city == dst) {
                best = std::min(best, elem.cost);
                best_way[elem.city] = best;
                continue;
            }
            
            if (elem.hop == k) continue;  // prune here
            if (best_way.find(elem.city) == best_way.end() || best_way[elem.city] > elem.cost) {
                best_way[elem.city] = elem.cost;
            } else {
                continue;  // prune here
            }
            
            for (const auto& neigh : graph[elem.city]) {                
                if (elem.cost + neigh.second >= best) continue;
                q.push({neigh.first, elem.cost+neigh.second, elem.hop+1});
            }
        }
        
        return (best == std::numeric_limits<int>::max() ? -1 : best);
    }
};

