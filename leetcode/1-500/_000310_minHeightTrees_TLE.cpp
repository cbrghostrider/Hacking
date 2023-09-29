class Solution {
    // Memoize this:
    // traverse from "came_from" to "node", what is the height of subtree at node?    
    unordered_map<int, int> cache;
    
    unordered_map<int, vector<int>> graph;
    int N;

    int signature(int node, int came_from) {
        int is_neg = came_from < 0 ? 0x1 : 0x0;
        int pos_came_from = std::abs(came_from);
        return ((node << 16) | (pos_came_from << 1) | (is_neg));
    }
    
    // get's height of subtree at "node", assuming parent was "came_from"
    int getHeight(int node, int came_from) {
        int sig = signature(node, came_from);
        if (cache.find(sig) != cache.end()) {
            return cache[sig];
        }
        
        int best=0;
        for (int neigh : graph[node]) {
            if (neigh == came_from) continue;
            int my_ht = 1 + getHeight(neigh, node);
            best = std::max(best, my_ht);
        }
        
        cache[sig] = best;
        return cache[sig];
    }
    
    void buildGraph(int n, const vector<vector<int>>& edges) {
        N = n;
        for (const vector<int>& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
    }
    
public:
    // 
    // Solution is functionally correct, but...
    // TLE for largest input (20k nodes), even with memoization.
    //
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        buildGraph(n, edges);
        
        int best=-1;
        vector<int> ans;
        
        for (int i=0; i<n; i++) {
            int ht = getHeight(i, -1);
            if (best == -1 || ht < best) {
                best = ht;
                ans.clear();
                ans.push_back(i);
            } else if (best == ht) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
