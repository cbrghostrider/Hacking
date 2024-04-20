// Pretty naive solution that leads to a TLE.
// 634/716 cases cleared.
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
    unordered_map<int, set<int>> path;
    unordered_map<int, int> distance;
    set<int> divisible;  // all nodes whose distance is signalSpeed divisible
};

void dfs(int node, int from_node, Info& info, int& total, set<int>& nodes, const int signalSpeed) {
    if (from_node != -1) {
        total += adj_list[from_node][node];
        nodes.insert(node);        
        info.path[node] = nodes;
        info.distance[node] = total;
        if (total % signalSpeed == 0) {info.divisible.insert(node);}
    }

    for (const auto& kv : adj_list[node]) {
        int neigh = kv.first;
        if (neigh == from_node) continue;
        dfs(neigh, node, info, total, nodes, signalSpeed);
    }

    if (from_node != -1) {
        total -= adj_list[from_node][node];
        nodes.erase(node);   
    }
}
public:
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed) {
        const int N = edges.size()+1;
        construct_adj_list(N, edges);
        vector<int> counts(N, 0);

        // vector<Info> infos(N, Info());        
        for (int c=0; c<N; c++) {
            Info info;
            set<int> nodes;
            int total=0;
            dfs(c, -1, info, total, nodes, signalSpeed);

            int count=0;
            for (auto it = info.divisible.begin(); it != info.divisible.end(); it++) {
                auto it2 = it; it2++;
                for (; it2 != info.divisible.end(); it2++) {
                    int n1 = *it, n2 = *it2;
                    vector<int> isec;
                    std::set_intersection(info.path[n1].begin(), info.path[n1].end(), info.path[n2].begin(), info.path[n2].end(), std::back_inserter(isec));
                    if (isec.empty()) {
                        count++;
                    }
                }
            }
            counts[c] = count;
        }
        
        return counts;
    }
};
