class Solution {
    class Diag {
      public:
        Diag(vector<vector<int>>& m, int start_row, int start_col)
            : mat(m), sr(start_row), sc(start_col) {
                const int R = m.size();
                const int C = m[0].size();
                int diag_size = std::min(R-sr, C-sc);
                diag = vector<int>(diag_size, 0);
                for (int ri=sr, ci=sc, d=0; d<diag_size; d++) {
                    diag[d] = mat[ri+d][ci+d];
                }
            }
        
        void sort() {
            std::sort(diag.begin(), diag.end());
            for (int ri=sr, ci=sc, d=0; d<diag.size(); d++) {
                mat[ri+d][ci+d] = diag[d];
            }
        }
        
      private:
        vector<vector<int>>& mat;
        vector<int> diag;
        const int sr, sc;
    };
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        const int R = mat.size();
        const int C = mat[0].size();
        for (int r=0; r<R; r++) {
            Diag diag(mat, r, 0);
            diag.sort();
        }
        for (int c=1; c<C; c++) {
            Diag diag(mat, 0, c);
            diag.sort();
        }
        return mat;
    }
};
