class Solution {

// Outer key: Node id
// Inner key: Adjacent node id
// Value: Weight of that edge
unordered_map<int, unordered_map<int, int>> adj_list;

void construct_adj_list(int n, const vector<vector<int>>& edges) {
    for (int i=0; i<n; i++) {adj_list[i] = {};}
    for (const auto& edge : edges) {
        int v1 = edge[0];
        int v2 = edge[1];
        int w = edge[2];
        adj_list[v1][v2] = w;
        adj_list[v2][v1] = w;
    }
}

struct Info {        
    vector<int> independent_counts;  // along a given direct edge from the main dfs master_node, how many signalSpeed modulo compliant nodes did we find.
    int divisible=0;                 // records the above nodes as needed, along the dfs from one DIRECT edge from the master_node.
};

void dfs(int node, int from_node, int master_node, Info& info, int& total, const int signalSpeed) {
    if (from_node != -1) {
        total += adj_list[from_node][node];        
        if (total % signalSpeed == 0) {info.divisible++;}
    }

    for (const auto& kv : adj_list[node]) {
        int neigh = kv.first;
        if (neigh == from_node) continue;
        dfs(neigh, node, master_node, info, total, signalSpeed);
    }

    if (from_node != -1) {
        total -= adj_list[from_node][node];        
    }
    if (from_node == master_node) {
        info.independent_counts.push_back(info.divisible);
        info.divisible = 0;        
    }
}
public:
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed) {
        const int N = edges.size()+1;
        construct_adj_list(N, edges);
        vector<int> counts(N, 0);
                
        for (int c=0; c<N; c++) {
            Info info;            
            int total=0;
            dfs(c, -1, c, info, total, signalSpeed);

            int count=0;
            for (int i=0; i<info.independent_counts.size(); i++) {
                for (int j=i+1; j<info.independent_counts.size(); j++) {
                    count += (info.independent_counts[i] * info.independent_counts[j]);
                }
            }
            counts[c] = count;
        }
        
        return counts;
    }
};
