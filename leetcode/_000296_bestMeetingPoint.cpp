class Solution {
    struct Coord {
        int r=0;
        int c=0;
    };    
    
    int distance(const Coord& a, const Coord& b) {
        return (std::abs(a.r-b.r) + std::abs(a.c-b.c));
    }
public:
    // TLE: Naive: O(R*R*C*C) time.
    int minTotalDistance_(vector<vector<int>>& grid) {
        const int R=grid.size();
        const int C=grid[0].size();
        
        vector<Coord> friends;
        vector<Coord> meetings;
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 1) {friends.push_back({r, c});}
                meetings.push_back({r, c});
            }
        } 
        
        int min_dist=std::numeric_limits<int>::max();
        for (const Coord& m : meetings) {
            int dist=0;
            for (const Coord& f : friends) {
                dist += distance(m, f);
            }
            min_dist = std::min(dist, min_dist);
        }
        
        return min_dist;
    }
    
    // Time: O(m * log R * log C): m == #friends
    // Basically, find the "center of mass" or "centroid" coordinate for friends.
    // Then look within +/- log R rows and +/- log C cols
    // \_ o _/
    int minTotalDistance(vector<vector<int>>& grid) {
        const int R=grid.size();
        const int C=grid[0].size();
        
        vector<Coord> friends;
        int sum_r=0, sum_c=0;
        
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 0) continue;
                sum_r += r;
                sum_c += c;
                friends.push_back({r, c});
            }
        }
        
        int count=friends.size();
        if (count == 0) return 0;
        
        Coord chosen = {sum_r/count, sum_c/count};        

        int min_dist=std::numeric_limits<int>::max();
        int dr = log2(R);
        int dc = log2(C);
        for (int delta_r=-1*dr; delta_r <= dr; delta_r++) {
            for (int delta_c=-1*dc; delta_c <= dc; delta_c++) {
                Coord cand = {chosen.r+delta_r, chosen.c+delta_c};
                if (cand.r <0|| cand.r >= R || cand.c<0 || cand.c >=C) continue;
                int dist=0;
                for (const Coord& f : friends) {
                    dist += distance(cand, f);
                }
                min_dist = std::min(dist, min_dist);
            }
        }
        return min_dist;
    }
};
