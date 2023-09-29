class Solution {
    struct Info {
        int run_left=0;    // the number of trailing 1's from the left
        int run_top=0;     // the number of trailing 1's from the top
    };    
public:
    // O(n^3) time, O(n^2) space.
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        const int R=grid.size();
        const int C=grid[0].size();
        
        vector<vector<Info>> infos(R, vector<Info>(C, Info()));
        
        // Get run_left and run_right values.
        for (int r=0; r<R; r++) {
            int run=0;
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 1) {run++;} else {run=0;}
                infos[r][c].run_left = run;
            }
        }
        
        // Get run_top and run_bottom values.
        for (int c=0; c<C; c++) {
            int run=0;
            for (int r=0; r<R; r++) {
                if (grid[r][c] == 1) {run++;} else {run=0;}
                infos[r][c].run_top = run;
            }          
        }
        
        int longest=0;
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (grid[r][c] == 0) continue;
                
                int len_lt = std::min(infos[r][c].run_left, infos[r][c].run_top);
                int my_longest=0;
                for (int d=0; d<len_lt; d++) {
                    int this_len = d+1;
                    if (infos[r-d][c].run_left >= this_len && 
                        infos[r][c-d].run_top >= this_len) {
                        my_longest = std::max(my_longest, this_len);
                    }
                }
                longest = std::max(my_longest, longest);
            }
        }
        return (longest*longest);
    }
};

