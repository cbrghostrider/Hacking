struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {        
        return (r == rhs.r && c == rhs.c);
    }
};
template<>
struct hash<Coord> {
size_t operator()(const Coord& key) const {
    return ((key.r << 16) | (key.c));
}
};
struct Info {
    Coord c;
    bool is_rotten=false;
    int time=0;
};
class Solution {

    int R, C;
public:
    // O(R*C) time BFS. 
    int orangesRotting(vector<vector<int>>& grid) {
        R=grid.size();
        C=grid[0].size();
        
        std::queue<Info> q;
        unordered_set<Coord> visited;
        int good=0;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 1) {good++; continue;}
                if (grid[r][c] == 0) {continue;}
                q.push({{r, c}, true, 0});
                visited.insert({r, c});
            }
        }
        
        auto shouldProcess = [&grid, &visited, this](const Coord& coord) -> bool {
            if (coord.r < 0 || coord.r == R || coord.c < 0 || coord.c == C) return false;
            return (grid[coord.r][coord.c] == 1 && visited.find(coord) == visited.end());
        };
        
        int time=0;
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            if (!elem.is_rotten) {  // fresh becomes rotten
                if (elem.time > time) {time = elem.time;}
                elem.is_rotten = true;
                good--;
            }
            Coord crd = elem.c;
            vector<Coord> neighs = {{crd.r-1, crd.c}, {crd.r+1, crd.c}, 
                                    {crd.r, crd.c-1}, {crd.r, crd.c+1}};
            for (const Coord& neigh : neighs) {
                if (!shouldProcess(neigh)) continue;
                visited.insert(neigh);
                q.push({neigh, false, elem.time+1});
            }
        }
        
        if (good != 0) return -1;
        return time;
    }
};
