// Solution below applies Floyd Warshall's "all pairs shortest paths" algorithm.
// Functionally correct, but gets TLE after 35/39 solutions.
// O(n^3) solution.
//
// Another solution repeatedly applied Dijkstra for all source nodes.
// Functionally correct, and this time AC!!
//
// Stupid that repeated Dijkstra works, but Floyd Warshall does not?
int N=0, K=0;
vector<int> applecosts;

struct Info {
    int city=0;
    long long opt=std::numeric_limits<int>::max();
};

bool Compare(const Info& lhs, const Info& rhs) {
    if (lhs.opt != rhs.opt) return lhs.opt > rhs.opt;
    return false;
}

class Dijkstra {
    // For each source node (key1), a map of destination nodes (key2) and edge weights.
    unordered_map<int, unordered_map<int, long long>> vedges;

    Info START;
    unordered_map<int, long long> optimums;   

public:

    void initialize(vector<vector<int>>& roads, vector<int>& appleCost) {
        for (const auto& road : roads) {
            int c1=road[0] - 1;
            int c2=road[1] - 1;
            int cost = road[2];
            vedges[c1][c2] = vedges[c2][c1] = cost;
        }
        applecosts = appleCost;
    }

    long long dijkstra(int start) {
        std::priority_queue<Info, vector<Info>, std::function<bool(const Info&, const Info&)>> heap(Compare);
        START.city=start;
        START.opt = 0;
        heap.push(START);
        optimums.clear();

        while (!heap.empty()) {            
            Info crd = heap.top();
            heap.pop();
            if (optimums.find(crd.city) != optimums.end()) {
                continue;
            }
            long long opt_cost = applecosts[crd.city] + crd.opt * (K+1);
            optimums[crd.city] = crd.opt;         

            // Figure out possible shorter paths from this node to its edges.
            for (const auto& kv : vedges[crd.city]) {
                Info tgt;
                tgt.city = kv.first;

                long long new_val = optimums[crd.city] + kv.second;                
                if (optimums.find(tgt.city) != optimums.end()) {
                    continue;
                }

                tgt.opt = new_val;
                heap.push(tgt);
            }
        }

        // Now get weighted path + applecost comparisons.
        long long best = std::numeric_limits<int>::max();
        for (const auto& kv : optimums) {
            int tgt_city = kv.first;
            long long scaled = kv.second * (K+1);
            long long apple = applecosts[tgt_city];
            scaled += apple;
            if (scaled < best) {
                best = scaled;
            }
        }
        return best;
        
        
    }
};

class FloydWarshall {
    // For floyd warshall's algorithm.
    vector<vector<long long>> dp;
public:
    void initialize(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {
        for (int i=0; i<n; i++) {
            dp.push_back(vector<long long>(n, std::numeric_limits<int>::max()));
            dp[i][i] = 0;            
        }
        
        for (const auto& road : roads) {
            int c1=road[0] - 1;
            int c2=road[1] - 1;
            int cost = road[2];
            dp[c1][c2] = dp[c2][c1] = cost;
        }
        applecosts = appleCost;
    }

    void floydWarshall() {
        for (int k=0; k<N; k++) {
            for (int i=0; i<N; i++) {
                for (int j=0; j<N; j++) {
                    if (dp[i][j] > dp[i][k] + dp[k][j]) {
                        dp[i][j] = dp[i][k] + dp[k][j];
                    }
                }
            }
        }
    }

    vector<long long> bestCosts() {
        vector<long long> ans;
        for (int i=0; i<N; i++) {
            long long best = std::numeric_limits<long long>::max();
            for (int j=0; j<N; j++) {
                long long scaled = dp[i][j] * (K+1);
                scaled += applecosts[j];
                if (best > scaled) {best = scaled;}
            }
            ans.push_back(best);
        }
        return ans;
    }
};

class Solution {
public:
    // This version runs Floyd Warshall, but is too slow (35/39 pass): O(n^3).
    vector<long long> minCost2(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {
        N=n;
        K=k;
        FloydWarshall fw;
        // Run all nodes shortest path.
        // For each node, multiply shortest path by (k+1).
        // For each path, add cost of apple at end node.
        // Find lowest value of (weighted path + cost of apple) options.
        fw.initialize(n, roads, appleCost, k);
        fw.floydWarshall();
        return fw.bestCosts();
    }

    // This version runs dijkstra from each source node.
    vector<long long> minCost(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {
        N=n;
        K=k;
        Dijkstra dj;
        dj.initialize(roads, appleCost);
        vector<long long> ans;
        for (int city=0; city<applecosts.size(); city++) {
            long long val = dj.dijkstra(city);
            ans.push_back(val);
        }
        return ans;
    }
};
