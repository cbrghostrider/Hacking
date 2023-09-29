class Solution {
    unordered_map<int, unordered_map<int, int>> graph;
    const int MINPATH=10;  // the min path value    

    struct Info {
        int me=-1;   // my node number
        unordered_set<int> visited;
        int time=0;  // the time used so far.
    };
    
    int evaluate(const unordered_set<int>& nodes, const vector<int>& vals) {
        int points=0;
        for (int n : nodes) {
            points += vals[n];
        }
        return points;
    }
    
    // how many hops is this node from source.
    // only contains nodes connected to src
    // used for early pruning
    unordered_map<int, int> hops_from_src;
    
    void computeHopsFromSrc() {
        unordered_set<int> visited;        
        std::queue<pair<int, int>> q;
        q.push({0, 0});
        visited.insert(0);
        
        while (!q.empty()) {
            auto elem=q.front(); q.pop();
            
            visited.insert(elem.first);
            hops_from_src[elem.first] = elem.second;
            
            for (const auto& kv : graph[elem.first]) {
                if (visited.find(kv.first) != visited.end()) continue;
                visited.insert(kv.first);
                q.push({kv.first, elem.second+1});
            }
        }
    }
public:
    //
    // Just a simple BFS with repeated nodes.
    // Currently gets a TLE, even with early pruning.
    //
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        for (const auto& edge : edges) {
            graph[edge[0]][edge[1]] = edge[2];
            graph[edge[1]][edge[0]] = edge[2];
        }
        
        computeHopsFromSrc();
        
        int best=values[0];
        std::queue<Info> q;
        q.push({0, {0}, 0});
        
        while (!q.empty()) {
            auto elem=q.front(); q.pop();
            if (elem.time > maxTime) continue;  // can't use this set anymore
            
            if (elem.me == 0) {
                int points = evaluate(elem.visited, values);
                best=std::max(best, points);
            }
            
            for (const auto& kv : graph[elem.me]) {
                int my_node = kv.first;
                int my_time = elem.time + kv.second;
                
                // Early pruning...
                if (my_time > maxTime) continue;
                int hops = hops_from_src[my_node];
                if (my_time + hops*MINPATH > maxTime) continue;
		// End early pruning...
                
                unordered_set<int> my_set = elem.visited;
                my_set.insert(my_node);
                q.push({my_node, my_set, my_time});
            }
        }
        return best;
    }
};
