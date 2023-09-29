class Solution {
    struct Info {
        int vert=0;
        int horiz=0;
        int diag=0;
        int antidiag=0;
    };
public:
    // O(RC) time, O(RC) space.
    int longestLine(vector<vector<int>>& mat) {
        const int R=mat.size();
        const int C=mat[0].size();
        
        vector<vector<Info>> infos(R, vector<Info>(C, Info()));
        
        int best=0;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (mat[r][c] == 0) continue;
                int v = r == 0 ? 1 : infos[r-1][c].vert + 1;
                int h = c == 0 ? 1 : infos[r][c-1].horiz + 1;
                int d = r == 0 || c == 0 ? 1 : infos[r-1][c-1].diag + 1;
                infos[r][c] = {v, h, d, 0};
                best = std::max(std::max(best, v), std::max(h, d));
            }
        }
        
        for (int r=0; r<R; r++) {
            for (int c=C-1; c>=0; c--) {
                if (mat[r][c] == 0) continue;
                int ad = r == 0 || c == C-1 ? 1 : infos[r-1][c+1].antidiag + 1;
                infos[r][c].antidiag = ad;
                best = std::max(best, ad);
            }
        }
        return best;
    }
};
