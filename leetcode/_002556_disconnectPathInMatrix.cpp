// Every path from start to end, contains the exact same number of steps
// this is due to the +1r or +1c requirement.
//
// We keep track of nodes that are simultaneously the same number of hops away from 
// the end.
// If there's only one such node, then flipping it will disconnect the matrix.
//
// Keep in mind that some nodes are reached from start, but cannot reach end.
// To filter these out, we do an initial traverse bfs.

struct Coord {
    int r=0;
    int c=0;
    bool operator==(const Coord& rhs) const {
        return (r == rhs.r && c == rhs.c);
    }
};

template<>
struct hash<Coord> {
    size_t operator()(const Coord& crd) const {
        return (((size_t)crd.r << 32) | (size_t)crd.c);
    }
};


class Solution {
    int R, C;

    // Mark all points reachable from origin as "2".
    void traverse(vector<vector<int>>& grid) {        
        queue<Coord> q;
        q.push({0, 0});
        while (!q.empty()) {
            Coord crd = q.front();
            q.pop();
            if (grid[crd.r][crd.c] == 2) continue;
            grid[crd.r][crd.c]++;
            if (crd.r != R-1 && grid[crd.r+1][crd.c] == 1) {q.push({crd.r+1, crd.c});}
            if (crd.c != C-1 && grid[crd.r][crd.c+1] == 1) {q.push({crd.r, crd.c+1});}
        }
    }

public:
    bool isPossibleToCutPath(vector<vector<int>>& grid) {
        R = grid.size();
        C = grid[0].size();
        traverse(grid);        

        unordered_set<Coord> seeds;
        seeds.insert({R-1, C-1});        

        while (1) {
            if (seeds.size() == 1) { 
                auto it = seeds.begin();
                Coord crd = *it;
                if (!((crd.r == R-1 && crd.c == C-1) || 
                      (crd.r == 0 && crd.c == 0)))  { 
                        // Exactly one node is available at this hop.
                        // We can flip this to disconnect the matrix.
                        return true; 
                }
            }
            if (seeds.size() == 0) {
                // Couldn't reach origin at all; trivially disconnected.
                return true;
            }
            unordered_set<Coord> newseeds;
            for (const Coord& c : seeds) {                
                if (c.r == 0 && c.c == 0) {
                    // Returned origin without finding disconnect node.
                    return false;
                }
             
                if (c.r != 0 && grid[c.r-1][c.c] == 2) newseeds.insert({c.r-1, c.c});
                if (c.c != 0 && grid[c.r][c.c-1] == 2) newseeds.insert({c.r, c.c-1});                
            }
            seeds = newseeds;
        }
        return false;
    }
};
