struct Coord {
    int xi=0;
    int yi=0;
    bool operator==(const Coord& rhs) const {
        return xi==rhs.xi && yi==rhs.yi;
    }
    bool operator<(const Coord& rhs) const {
        if (xi != rhs.xi) return xi < rhs.xi;
        return yi < rhs.yi;
    }
};
constexpr int DISPLACE = 10000;
template<>
struct hash<Coord> {
size_t operator()(const Coord& rhs) const {
    return (((DISPLACE+rhs.xi) << 16) | (DISPLACE+rhs.yi));
}
};
class Solution {
public:
    // 
    // Performing BFS from both directions (source and target)....
    // Still gets TLE...
    //
    int minKnightMoves(int x, int y) {
        unordered_map<Coord, int> visited_src, visited_tgt;
        std::queue<pair<Coord, int>> q1, q2;
        Coord source = {0, 0};
        Coord target = {x, y};
        
        q1.push({source, 0});
        visited_src[source] = 0;
        q2.push({target, 0});
        visited_tgt[target] = 0;
        
        unordered_map<Coord, int>* v_ptr = &visited_src;
        unordered_map<Coord, int>* other_v_ptr = &visited_tgt;
        std::queue<pair<Coord, int>>* q_ptr=&q1;
        bool turn_1 = true;  // q1's turn
        
        while (!q_ptr->empty()) {
            Coord cmp = turn_1 ? target : source;
            
            auto elem=q_ptr->front(); q_ptr->pop();
            
            Coord crd = elem.first;
            int dist = elem.second;
            if (crd == cmp) {
                return dist;
            }
            
            vector<Coord> neighs = {
                {crd.xi-2, crd.yi+1}, {crd.xi-1, crd.yi+2}, {crd.xi+1, crd.yi+2}, {crd.xi+2, crd.yi+1},
                {crd.xi-2, crd.yi-1}, {crd.xi-1, crd.yi-2}, {crd.xi+1, crd.yi-2}, {crd.xi+2, crd.yi-1}
            };
            for (const Coord& neigh : neighs) {
                if (other_v_ptr->find(neigh) != other_v_ptr->end()) {
                    // got mapped from the other direction
                    int total_dist = (*other_v_ptr)[neigh] + dist + 1;
                }
                if (v_ptr->find(neigh) != v_ptr->end()) { continue; }                
                
                (*v_ptr)[neigh] = dist+1;
                q_ptr->push({neigh, dist+1});
            }
            
            turn_1 = !turn_1;
            v_ptr = turn_1 ? &visited_src : &visited_tgt;
            other_v_ptr = turn_1 ? &visited_tgt : &visited_src;
            q_ptr = turn_1 ? &q1 : &q2;
        }
        return -1;
    }
};
