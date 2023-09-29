struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {
        return (r == rhs.r && c == rhs.c);
    }
};

template<>
struct hash<Coord> {
size_t operator()(const Coord& coord) const {
    return ((coord.r << 5) | (coord.c));
}
};

struct DynInfo {
    Coord box;     // this is where the box is currently
    Coord player;  // this is where the player is currently
    int pushes=0;  // this is how many pushes have been done so far
    
    // Generates a hash value that can be used to memoize this config.
    int hashVal() const {
        return ((box.r << 15) | (box.c << 10) | (player.r << 5) | (player.c));
    }
};

class Solution {
    vector<vector<char>> grid;
    int R, C;
    Coord TARGET;

    // box will act as temporary obstacle for this purpose
    // can player at "player" get to location at "location"
    bool playerCanGetTo(const Coord& box, const Coord& player, const Coord& location) {
        // if (box == player || box == location) return false;
        
        unordered_set<Coord> visited;
        visited.insert(player);
        
        queue<Coord> q;
        q.push(player);
        
        while (!q.empty()) {
            auto crd = q.front(); q.pop();
            if (crd == location) return true;
            
            vector<Coord> neighs = {
                {crd.r-1, crd.c}, {crd.r+1, crd.c},
                {crd.r, crd.c-1}, {crd.r, crd.c+1}
            };
            
            for (const Coord& neigh : neighs) {
                if (neigh.r < 0 || neigh.r == R || neigh.c < 0 || neigh.c == C) continue;
                if (neigh == box) continue;
                if (grid[neigh.r][neigh.c] == '#') continue;
                if (visited.find(neigh) != visited.end()) continue;
                visited.insert(neigh);
                q.push(neigh);
            }
        }
        return false;
    }
    
    // returns player location for box to be pushed to where it needs to go
    pair<bool, Coord> getPlayerLocationToMoveBox(const Coord& box_at, const Coord& box_to) {
        // Has to be within bounds.
        if (box_to.r < 0 || box_to.r == R || box_to.c < 0 || box_to.c == C) return {false, {}};
        
        // Has to not be an obstacle.
        if (grid[box_to.r][box_to.c] == '#') return {false, {}};
        
        // Trying to move diagonally or weirdly.
        if (box_to.r != box_at.r && box_to.c != box_at.c) return {false, {}};
        
        Coord ret;        
        if (box_to.r == box_at.r) {
            ret.r = box_to.r;
            ret.c = box_to.c > box_at.c ? box_at.c-1 : box_at.c+1;
            if (ret.c < 0 || ret.c == C) return {false, {}};
        } else {
            ret.c = box_to.c;
            ret.r = box_to.r > box_at.r ? box_at.r-1 : box_at.r+1;
            if (ret.r < 0 || ret.r == R) return {false, {}};
        }
        return {true, ret};
    }
    
public:
    int minPushBox(vector<vector<char>>& g) {
        grid = g;
        R = grid.size();
        C = grid[0].size();
        
        Coord player, box, target;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 'T') {
                    target = {r, c};
                } else if (grid[r][c] == 'B') {
                    box = {r, c};
                } else if (grid[r][c] == 'S') {
                    player = {r, c};
                }
            }
        }
        TARGET = target;
        
        // hashval -> min pushes so far
        unordered_map<int, int> cache;
        
        DynInfo dinfo = {box, player, 0};
        cache[dinfo.hashVal()] = 0;
        
        auto comp = [&target](const DynInfo& lhs, const DynInfo& rhs) -> bool {
            int lhsheur = std::abs(target.r-lhs.box.r) + std::abs(target.c-lhs.box.c) + lhs.pushes;
            int rhsheur = std::abs(target.r-rhs.box.r) + std::abs(target.c-rhs.box.c) + rhs.pushes;
            if (lhsheur != rhsheur) return lhsheur > rhsheur;
            return false;
        };
        
        priority_queue<DynInfo, vector<DynInfo>, decltype(comp)> q(comp);
        q.push(dinfo);
        
        while (!q.empty()) {
            DynInfo dinfo = q.top(); q.pop();
            if (dinfo.box == TARGET) {
                return dinfo.pushes;
            }
            
            int hv = dinfo.hashVal();
            if (cache.find(hv) != cache.end() && cache[hv] < dinfo.pushes) {
                continue;
            }
            
            vector<Coord> bneighs = {
                {dinfo.box.r-1, dinfo.box.c}, {dinfo.box.r+1, dinfo.box.c},
                {dinfo.box.r, dinfo.box.c-1}, {dinfo.box.r, dinfo.box.c+1}
            };            
            
            for (const Coord& bn : bneighs) {
                auto possLoc = getPlayerLocationToMoveBox(dinfo.box, bn);
                if (possLoc.first == false) continue;
                
                bool canMove = playerCanGetTo(dinfo.box, dinfo.player, possLoc.second);
                if (!canMove) continue;
                
                DynInfo my_info = {bn, dinfo.box, dinfo.pushes+1};
                
                int hv = my_info.hashVal();
                if (cache.find(hv) != cache.end() && cache[hv] < dinfo.pushes+1) {
                    continue;
                }
                cache[hv] = dinfo.pushes+1;                
                
                q.push(my_info);
            }
        }
        
        return -1;
    }
}; 
