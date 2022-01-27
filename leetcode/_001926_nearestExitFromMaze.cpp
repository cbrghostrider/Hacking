#include <functional>
    struct Coord {
        int r=0;
        int c=0;
        bool operator==(const Coord& rhs) const {
            return (r == rhs.r && c == rhs.c);
        }
        bool operator!=(const Coord& rhs) const {
            return !(*this == rhs);
        }
    };

    template<>
    struct std::hash<Coord> {
        size_t operator()(const Coord& crd) const {
            return ((crd.r << 16) | (crd.c));
        }
    };

class Solution {    
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        const int R=maze.size();
        const int C=maze[0].size();
        
        Coord source = {entrance[0], entrance[1]};
        // (crd, dist)
        queue<pair<Coord, int>> q;
        q.push({source, 0});
        unordered_set<Coord> visited;
        visited.insert(source);
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            Coord crd = elem.first;
            if ((crd != source) && (crd.r == 0 || crd.r == R-1 || crd.c == 0 || crd.c == C-1)) {
                return elem.second;
            }
            
            vector<Coord> neighs = {
                {crd.r-1, crd.c}, {crd.r+1, crd.c},
                {crd.r, crd.c-1}, {crd.r, crd.c+1},
            };
            
            for (const Coord& neigh : neighs) {
                if (neigh.r < 0 || neigh.r >= R || neigh.c < 0 || neigh.c >= C) continue;
                if (maze[neigh.r][neigh.c] == '+') continue;
                if (visited.find(neigh) != visited.end()) continue;
                visited.insert(neigh);
                q.push({neigh, elem.second+1});
            }                
        }
        return -1;
    }
};
