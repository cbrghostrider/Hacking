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
    // TLE? WTF?
    // Solution is functionally correct.
    int minKnightMoves(int x, int y) {
        unordered_set<Coord> visited;
        std::queue<pair<Coord, int>> q;
        q.push({{0, 0}, 0});
        visited.insert({0, 0});
        
        while (!q.empty()) {
            auto elem=q.front(); q.pop();
            Coord crd = elem.first;
            int dist = elem.second;
            if (crd.xi == x && crd.yi == y) {
                return dist;
            }
            
            vector<Coord> neighs = {
                {crd.xi-2, crd.yi+1}, {crd.xi-1, crd.yi+2}, {crd.xi+1, crd.yi+2}, {crd.xi+2, crd.yi+1},
                {crd.xi-2, crd.yi-1}, {crd.xi-1, crd.yi-2}, {crd.xi+1, crd.yi-2}, {crd.xi+2, crd.yi-1}
            };
            for (const Coord& neigh : neighs) {
                if (visited.find(neigh) != visited.end()) continue;
                visited.insert(neigh);
                q.push({neigh, dist+1});
            }
        }
        return -1;
    }
};
