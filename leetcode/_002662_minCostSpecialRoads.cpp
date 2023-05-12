struct Coord {
    int x=0;
    int y=0;
    // The best cost path to this node from start.
    int opt=std::numeric_limits<int>::max();
    // Needed by hash table.
    bool operator==(const Coord& rhs) const {
        return (x == rhs.x && y == rhs.y);
    }
    bool operator<(const Coord& rhs) const {
        if (x == rhs.x && y == rhs.y) return false;
        return (x < rhs.x || y < rhs.y);
    }
    Coord() : x(0), y(0), opt(std::numeric_limits<int>::max()) {}
    Coord(int xi, int yi) : x(xi), y(yi), opt(std::numeric_limits<int>::max()) {}
};

template<>
struct hash<Coord> {
    std::size_t operator()(const Coord& crd) const {
        return (size_t)(((size_t)crd.x << 32) | ((size_t)crd.y));
    }
};

bool Compare(const Coord& lhs, const Coord& rhs) {
    if (lhs.opt != rhs.opt) return lhs.opt > rhs.opt;
    return false;
}

class Solution {
    Coord START, TARGET;
    int skip_after=0;

    // For each source node (key1), a map of destination nodes (key2) and edge weights.
    unordered_map<Coord, unordered_map<Coord, int>> vedges;
    unordered_map<Coord, int> optimums;

    int manhattan(const Coord& src, const Coord& dst) {
        return (std::abs(src.x-dst.x) + std::abs(src.y-dst.y));
    }

    void initialize(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        START = Coord(start[0], start[1]);
        TARGET = Coord(target[0], target[1]);
        vedges[START] = {};
        vedges[TARGET] = {};

        // If any edges are greater than this distance, don't bother.
        skip_after = manhattan(START, TARGET);

        for (const vector<int>& road : specialRoads) {
            Coord crd1 = Coord(road[0], road[1]);
            if (vedges.find(crd1) == vedges.end()) {
                vedges[crd1] = {};
            }
            Coord crd2 = Coord(road[2], road[3]);            
            if (vedges.find(crd2) == vedges.end()) {
                vedges[crd2] = {};
            }            
        }
        for (const auto& kv : vedges) {
            Coord src = kv.first;
            for (const auto& kv2 : vedges) {
                Coord dst = kv2.first;
                if (src == dst) continue;
                int dist = manhattan(src, dst);
                if (dist > skip_after) continue;
                vedges[src][dst] = manhattan(src, dst);
            }
        }
        // Correct for special roads.
        for (const vector<int>& road : specialRoads) {
            Coord src = Coord(road[0], road[1]);
            Coord dst = Coord(road[2], road[3]);
            if (road[4] > skip_after) continue;
            if (road[4] < vedges[src][dst]) {
                vedges[src][dst] = road[4];
            }
        }
    }    

    void dijkstra() {
        std::priority_queue<Coord, vector<Coord>, std::function<bool(const Coord&, const Coord&)>> heap(Compare);
        START.opt = 0;
        heap.push(START);        

        while (!heap.empty()) {            
            Coord crd = heap.top();
            heap.pop();
            if (optimums.find(crd) != optimums.end()) {
                continue;
            }
            optimums[crd] = crd.opt;
            if (crd == TARGET) break;

            // Figure out possible shorter paths from this node to its edges.
            for (const auto& kv : vedges[crd]) {
                Coord tgt = kv.first;
                                
                if (optimums.find(tgt) != optimums.end()) {
                    continue;
                }

                int new_val = optimums[crd] + kv.second;
                if (new_val > skip_after) continue;
                tgt.opt = new_val;
                heap.push(tgt);
            }
        }
    }
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        // First find all nodes N = {(xi, yi)}; (xi, yi) are all the special road start/end, and my start, and my target.
        // Then join each node to every other node, with an edge between 2 nodes with the cost:
        //    For nodes consisting of 2 ends of a special road, the cost is as stated.
        //    Else, cost is manhattan distance.
        // Run shortest path algorithm from my start to my target.
        initialize(start, target, specialRoads);
        dijkstra();
        return optimums[TARGET];

    }
};
