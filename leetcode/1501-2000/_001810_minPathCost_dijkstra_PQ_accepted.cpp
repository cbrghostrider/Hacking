/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     int move(char direction);
 *     boolean isTarget();
 * };
 */
struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {
        return (r == rhs.r && c == rhs.c);
    }
    bool operator<(const Coord& rhs) const {
        if (r != rhs.r) return r < rhs.r;
        return c < rhs.c;
    }
};
struct Info {
    bool can_move;
    int cost;
};

template<>
struct hash<Coord> {
size_t operator()(const Coord& key) const {
  return ((key.r << 16) | (key.c));
}
};

class Solution {
    unordered_map<Coord, int> cells;
    Coord source, target;
    GridMaster* gm = nullptr;
    
    // populates cells with information about the grid
    // Treats the starting cell as (101, 101), everything is relative to this cell.
    // to_reset tells the robot where to move to at the end after recursion is done
    void discover(Coord my_coord, char to_reset) {
        if (gm->isTarget()) {target = my_coord;}
        if (gm->canMove('U') && cells.find({my_coord.r-1, my_coord.c}) == cells.end()) {
            cells[{my_coord.r-1, my_coord.c}] = gm->move('U');
            discover({my_coord.r-1, my_coord.c}, 'D');
        }
        if (gm->canMove('D') && cells.find({my_coord.r+1, my_coord.c}) == cells.end()) {
            cells[{my_coord.r+1, my_coord.c}] = gm->move('D');
            discover({my_coord.r+1, my_coord.c}, 'U');
        }
        if (gm->canMove('L') && cells.find({my_coord.r, my_coord.c-1}) == cells.end()) {
            cells[{my_coord.r, my_coord.c-1}] = gm->move('L');
            discover({my_coord.r, my_coord.c-1}, 'R');
        }
        if (gm->canMove('R') && cells.find({my_coord.r, my_coord.c+1}) == cells.end()) {
            cells[{my_coord.r, my_coord.c+1}] = gm->move('R');
            discover({my_coord.r, my_coord.c+1}, 'L');
        }
        if (to_reset != '*') {
            gm->move(to_reset);
        }
    }
    
    // returns min-cost to move from source to target
    // But the min-cost path isn't necessarily the min-hop path! 
    // We basically have a directed graph with non-negative edge weights.
    // So we have to run Dijkstra. Are you kidding me?
    int dijkstra() {
        auto comp = [](const pair<Coord, int>& lhs, const pair<Coord, int>& rhs) -> bool {
            return lhs.second > rhs.second;
        };
        unordered_set<Coord> q;
        priority_queue<pair<Coord, int>, vector<pair<Coord, int>>, decltype(comp)> pq(comp);
        map<Coord, int> dist;
        
        for (const auto& kv : cells) {
            q.insert(kv.first);
            pq.push({kv.first, std::numeric_limits<int>::max()});
            dist[kv.first] = std::numeric_limits<int>::max();
        }
        pq.push({source, 0});
        dist[source] = 0;
        
        
        while (!pq.empty()) {
            auto elem = pq.top(); pq.pop();
            Coord min_crd = elem.first;
            int min_dist = elem.second;
            if (dist[min_crd] < min_dist) continue;
            dist[min_crd] = min_dist;
            q.erase(min_crd);
            
            vector<Coord> crds = {
                {min_crd.r-1, min_crd.c}, {min_crd.r+1, min_crd.c},
                {min_crd.r, min_crd.c-1}, {min_crd.r, min_crd.c+1}
            };
            for (const Coord& c : crds) {
                if (q.find(c) != q.end()) {
                    int alt = dist[min_crd] + cells[c];
                    if (alt < dist[c]) {
                        dist[c] = alt;
                        pq.push({c, alt});
                    }
                }
            }
        }
        return dist[target];
    }
    
public:
    int findShortestPath(GridMaster &master) {
        gm = &master;
        source = {101, 101};
        target = {-1, -1};
        discover(source, '*');
        if (target == Coord{-1, -1}) return -1;
        return dijkstra();
    }
};
