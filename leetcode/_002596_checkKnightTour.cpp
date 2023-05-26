class Solution {
    struct Coord {
        int r=0;
        int c=0;
        int val=-1;
    };

    bool isMoveValid(const Coord& from, const Coord& to) {
        int delta_r = std::abs(from.r - to.r);
        int delta_c = std::abs(from.c - to.c);
        if (to.val != from.val + 1) return false;
        if (delta_r == 1 && delta_c == 2) return true;
        if (delta_r == 2 && delta_c == 1) return true;
        return false;
    }

public:
    bool checkValidGrid(vector<vector<int>>& grid) {        
        vector<Coord> crds;
        unordered_set<int> found;  // spot duplicates
        for (int r=0; r<grid.size(); r++) {
            for (int c=0; c<grid[0].size(); c++) {
                if (found.find(grid[r][c]) != found.end()) return false;  // duplicate
                crds.push_back({r, c, grid[r][c]});
                found.insert(grid[r][c]);
            }
        }

        std::sort(crds.begin(), crds.end(), [](const Coord& lhs, const Coord& rhs)->bool {
            if (lhs.val == rhs.val) return false;
            return lhs.val < rhs.val;
        });

        Coord last = crds[0];
        if (!(last.r == 0 && last.c == 0)) return false;
        for (int i=1; i<crds.size(); i++) {
            if (!isMoveValid(last, crds[i])) return false;
            last = crds[i];
        }
        return true;
    }
};
