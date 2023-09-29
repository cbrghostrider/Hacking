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
    // Tried to improve on the previous solution, by first examining more promising candidates
    // (see fcoords sorting).
    // But still TLE.
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
            
            vector<Coord> fcoords, coords = {
                {crd.r-1, crd.c}, {crd.r+1, crd.c}, {crd.r, crd.c-1}, {crd.r, crd.c+1}
            };
            for (const Coord& c : coords) {
                if (c.r == -1 || c.r == M || c.c == -1 || c.c == N) {continue;}
                fcoords.push_back(c);
            }
            std::sort(fcoords.begin(), fcoords.end(), [&grid](const Coord& lhs, const Coord& rhs) -> bool {
                return grid[lhs.r][lhs.c] > grid[rhs.r][rhs.c];
            });
            
            for (const Coord& c : fcoords) {
                int min_s = std::min(crd_score, grid[c.r][c.c]);
                if (shouldEval(c, min_s)) {
                    q.push({c, min_s});
                }                
            }            
        }
        return scores[end];
    }
};
