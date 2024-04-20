class Solution {

// Outer key: node (from)
// Inner key: node (to)
// Value: Weight of the edge
unordered_map<int, unordered_map<int, int>> adj_list;

struct Info {
    int node=0;  // the node to explore.
    int time=0;  // the current time at this node.
};

void build_graph(const vector<vector<int>>& edges) {
    for (const auto& e : edges) {
        int from = e[0], to = e[1], time = e[2];
        adj_list[from][to] = time;
    }
}

struct Edge {
    int from=0;
    int to=0;
    int time=0;
};

typedef std::function<bool (const Edge&, const Edge&)> EdgeComp;
typedef std::priority_queue<Edge, vector<Edge>, EdgeComp> MinHeap;

public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        build_graph(times);

        // The nodes that have received the signal.
        unordered_map<int, int> received;
        EdgeComp comp = [](const Edge& lhs, const Edge& rhs) -> bool {
            if (lhs.time != rhs.time) return lhs.time > rhs.time;
            if (lhs.from != rhs.from) return lhs.from > rhs.from;
            return lhs.to > rhs.to;
        };

        // Dijkstra's one-source, all-destinations shortest-path algorithm.
        MinHeap mh(comp);
        for (const auto& kv : adj_list[k]) {
            mh.push({k, kv.first, kv.second});
        }
        received[k] = 0;

        while (!mh.empty()) {
            Edge edge = mh.top(); mh.pop();
            if (received.find(edge.to) != received.end()) continue;
            received[edge.to] = edge.time;

            for (const auto& kv : adj_list[edge.to]) {
                int next_node = kv.first, next_time = edge.time + kv.second;
                if (received.find(next_node) != received.end()) continue;
                Edge new_edge = {edge.to, next_node, next_time};
                mh.push(new_edge);
            }
        }

        if (received.size() != n) {
            return -1;
        }

        // The longest shortest path is the minimum time it will take.
        int ret=-1;
        for (const auto& kv : received) {
            ret = std::max(ret, kv.second);
        }
        return ret;
    }
};
