class Solution {
    // stores the lengths of 1's upwards and leftwards from any cell (r, c).
    struct Runs {
        int up_len=0;
        int left_len=0;
    };
public:
    // O(M*N*N) time, O(M*N) space.
    // Possibly reduce to O(M*N) time by using monotonic stack instead of 
    // running innermost while loop always for length O(N).
    int numSubmat(vector<vector<int>>& mat) {
        const int M=mat.size();
        const int N=mat[0].size();
        
        vector<vector<Runs>> runs(M, vector<Runs>(N, {0,0}));
        for (int r=0; r<M; r++) {
            int run=0;
            for (int c=0; c<N; c++) {
                if (mat[r][c] == 1) {run++;} else {run=0;}
                runs[r][c].left_len = run;
            }
        }
        for (int c=0; c<N; c++) {    
            int run=0;
            for (int r=0; r<M; r++) {
                if (mat[r][c] == 1) {run++;} else {run=0;}
                runs[r][c].up_len = run;
            }
        }
        
        // For any cell (r, c), compute how many new 1' submatrices are produced with this cell as it's bottom right.
        // Add submatrices going upwards and leftwards, and subtract submatrices that are common to both.
        
        int count=0;
        for (int r=0; r<M; r++) {
            for (int c=0; c<N; c++) {
                int left_run_limit = std::numeric_limits<int>::max();
                for (int i=r; i>=0; i--) {
                    left_run_limit = std::min(left_run_limit, runs[i][c].left_len);
                    if (left_run_limit == 0) {break;}
                    count += left_run_limit;
                }
            }
        }
        return count;
    }
};
