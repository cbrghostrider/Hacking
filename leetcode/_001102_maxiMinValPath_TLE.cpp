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

class Solution {

public:
    // BFS solution.
    // Solution is functionally correct, but currently getting TLE.
    // This is because it isn't O(m*n) anymore, since we need to potentially re-evaluate 
    // crds again, if we find better paths.
    int maximumMinimumPath(vector<vector<int>>& grid) {
        // max score found so far for various coords;
        unordered_map<Coord, int> scores;
        const int M=grid.size(), N=grid[0].size();
        const Coord end = {M-1, N-1};
        
        // (crd, score)
        std::queue<pair<Coord, int>> q;
        q.push({{0, 0}, grid[0][0]});
        
        auto shouldEval = [&scores](const Coord& crd, int new_score) -> bool {
            bool dont = (scores.find(crd) != scores.end() && scores[crd] >= new_score);
            return !dont;
        };
        
        while (!q.empty()) {
            auto elem = q.front(); q.pop();
            Coord crd = elem.first;
            int crd_score = elem.second;
            if (!shouldEval(crd, crd_score)) {
                // We don't need to re-evaluate, since we can't increase score.
                continue;  
            }
            scores[crd] = crd_score;
            if (crd == end) continue;
            
            if (crd.r != 0) {
                Coord north = {crd.r-1, crd.c};
                int min_s = std::min(crd_score, grid[north.r][north.c]);
                if (shouldEval(north, min_s)) {
                    q.push({north, min_s});
                }
            }
            if (crd.r != M-1) {
                Coord south = {crd.r+1, crd.c};
                int min_s = std::min(crd_score, grid[south.r][south.c]);
                if (shouldEval(south, min_s)) {
                    q.push({south, min_s});
                }
            }
            if (crd.c != 0) {
                Coord west = {crd.r, crd.c-1};
                int min_s = std::min(crd_score, grid[west.r][west.c]);
                if (shouldEval(west, min_s)) {
                    q.push({west, min_s});
                }
            }    
            if (crd.c != N-1) {
                Coord east = {crd.r, crd.c+1};
                int min_s = std::min(crd_score, grid[east.r][east.c]);
                if (shouldEval(east, min_s)) {
                    q.push({east, min_s});
                }
            }                  
        }
        return scores[end];
    }
};
