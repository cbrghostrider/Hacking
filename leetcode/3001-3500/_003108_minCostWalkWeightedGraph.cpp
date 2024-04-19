class Solution {
// The key insight is found by considering the following expression:
// a & b & c
// Now if I add another operand: a & b & c & d
// The addition of (& d) CANNOT POSSIBLY make the value worse (bigger). 
// In the worst case (d = -1) it remains unchanged. In every other case, it is either unchanged or reduced.
//
// So we can blindly find the "islands" of connected vertices.
// Within each island, take the bitwise AND of every edge weight, and that's the min-cost from any vertex to any other vertex in that island.
// If the two vertices are on different islands, then the cost is -1 (impossible).
//

int inum = 0;
string next_island() {
    string ret = "island_" + std::to_string(inum++);
    return ret;
}

// Key: Island name; Value: The cost of AND-ing all the edges in that island.
map<string, int> costs;
// Key: vertex id; Value: it's island name
map<int, string> vertex_to_island;

// Key: vertex id
// Value: A map of:
//        Key: adjacent vertex id
//        Value: the cost of the edge between these two vertices
map<int, map<int, int>> adj_list;

void record_edge(int v1, int v2, int w) {
    if (adj_list[v1].find(v2) == adj_list[v1].end()) {
        adj_list[v1][v2] = w;
    } else {
        adj_list[v1][v2] &= w;
    }
}

void create_adj_list(int n, vector<vector<int>>& edges) {
    for (int v=0; v<n; v++) {
        adj_list[v] = {};
    }
    for (const auto& einfo : edges) {
        int v1 = einfo[0];
        int v2 = einfo[1];
        int w = einfo[2];
        record_edge(v1, v2, w);
        if (v1 != v2) record_edge(v2, v1, w);
    }
}

void dfs(const string& island, int v) {
    vertex_to_island[v] = island;
    for (const auto& kv : adj_list[v]) {
        costs[island] &= kv.second;        
    }
    for (const auto& kv : adj_list[v]) {
        if (vertex_to_island.find(kv.first) == vertex_to_island.end()) {
            dfs(island, kv.first);
        }
    }
}

public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        create_adj_list(n, edges);

        for (int v=0; v<n; v++) {
            if (vertex_to_island.find(v) != vertex_to_island.end()) {
                continue;  // already processed.
            }
            string island = next_island();
            costs[island] = -1;  // 0xffff...fff
            dfs(island, v);  // find this connected island.
        }

        vector<int> answers;
        for (const auto& q : query) {
            int v1 = q[0];
            int v2 = q[1];
            if (vertex_to_island[v1] != vertex_to_island[v2]) {
                answers.push_back(-1);
            } else {
                answers.push_back(costs[vertex_to_island[v1]]);
            }
        }
        return answers;
    }
};
