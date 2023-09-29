/**
 * // This is the GridMaster's API interface.
 * // You should not implement it, or speculate about its implementation
 * class GridMaster {
 *   public:
 *     bool canMove(char direction);
 *     void move(char direction);
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

template<>
struct hash<Coord> {
size_t operator()(const Coord& key) const {
    return ((key.r << 16) | (key.c));
}
};

// 
// This solution is functionally correct, but,
// it currently gets a TLE for large inputs (500 = R = C).
//
class Solution {
    unordered_map<Coord, unordered_set<Coord>> grid;
    unordered_set<Coord> visited;
    
    Coord source, target;
    GridMaster* gm = nullptr;
    
    char antiDirection(char ch) {
        switch (ch) {
            case 'U': return 'D';
            case 'D': return 'U';
            case 'L': return 'R';
            case 'R': return 'L';
        }
        return ' '; // should not get here...
    }
    
    // Discovers the grid structure using DFS.
    // robot is at cell elem at the start, 
    // and leaves discover routine by returning to cell elem.
    void discover(Coord elem) {   
        if (gm->isTarget()) {
            target = elem;
            return;
        }
        
        vector<pair<char, Coord>> neighs = {
            {'U', {elem.r-1, elem.c}}, {'D', {elem.r+1, elem.c}}, 
            {'L', {elem.r, elem.c-1}}, {'R', {elem.r, elem.c+1}}
        };
        for (const auto& neigh : neighs) {
            Coord crd = neigh.second;
            char dir = neigh.first;
            if (gm->canMove(dir) == false) continue;  // this is blocked
            grid[elem].insert(crd);   // this is one of my neighbors
            if (visited.find(crd) != visited.end()) continue;  // already mapped
            visited.insert(crd);
            // map it
            gm->move(dir);
            discover(crd);
            gm->move(antiDirection(dir));
        }        
    }
    
    // Finds the shortest path using BFS and the grid structure.
    int route() {        
        std::queue<pair<Coord, int>> q;
        q.push({source, 0});
        visited.insert(source);
        
        while (!q.empty()) {
            auto elem=q.front(); q.pop();
            Coord crd = elem.first;
            int dist = elem.second;
            if (crd == target) return dist;
            
            for (const Coord& neigh : grid[crd]) {
                if (visited.find(neigh) != visited.end()) continue;
                visited.insert(neigh);
                q.push({neigh, dist+1});
            }
        }
        return -1;  // target not found... should not happen.
    }
public:
    int findShortestPath(GridMaster &master) {
        gm = &master;
        // By assigning the source thus, we can hash the coord key properly.
        // since no r/c are negative (left shift is valid).
        source = {501, 501};  // beyond max range
        visited.insert(source);
        discover(source);
        
        visited.clear();
        int dist = route();
        return dist;
    }
};
