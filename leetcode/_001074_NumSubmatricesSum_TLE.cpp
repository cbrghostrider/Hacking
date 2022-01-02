class Solution {
    // let dp(i, j) denote all the submatrices of the matrix from (0, 0) top left, 
    // to (i, j) bottom right that satisfy the answer.
    // 
    // dp(i, j) = dp(i-1, j) + dp(i, j-1) - dp(i-1, j-1) + Sc
    // Sc = # of submatrices that satisfy the answer and have (i, j) 
    // as bottom right corner
    //
    
    int R, C;
    vector<vector<int>> csum, vert_sums;
    vector<vector<int>> sc, dp;
    
    // For submatrix with (r, c) at bottom right:
    // If "key_outer" is height of the submatrix, 
    // For each submatrix that adds up to "key_inner", 
    // how many (value) such submatrices are there?
    vector<vector<unordered_map<int, unordered_map<int, int>>>> smm; 
    
    void computeCSumsVSums(const vector<vector<int>>& matrix) {
        int sum=0;
        for (int c=0; c<C; c++) {
            int vert_sum=0;
            
            for (int r=0; r<R; r++) {            
                sum += matrix[r][c];
                vert_sum += matrix[r][c];
                
                csum[r][c] = sum;
                vert_sums[r][c] = vert_sum;
            }
        }        
    }
   
    // TLE, most likely because this is taking too long. 
    // I need to combine the inner and outer keys into one key... 
    void populateSmmSc(int target) {
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                auto& outer_map = smm[r][c];
                int count=0;   // counts how many add up to target (to populate Sc)
                for (int h=1; h<=r+1; h++) {
                    auto& inner_map = outer_map[h];
                    int vert_segment_sum = (r-h < 0) ? vert_sums[r][c]: vert_sums[r][c] - vert_sums[r-h][c];
                    if (c == 0) {
                        inner_map[vert_segment_sum]++;
                    } else {
                        inner_map[vert_segment_sum]++;
                        
                        auto& prev_col_map = smm[r][c-1][h];
                        for (const auto& kv : prev_col_map) {
                            int sub_target = kv.first + vert_segment_sum;
                            inner_map[sub_target] += kv.second;
                        }
                    }
                    count += inner_map[target];
                }
                sc[r][c] = count;
            }
        }
    }
    
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        R=matrix.size();
        C=matrix[0].size();
        
        dp = vert_sums = sc = csum = vector<vector<int>>(R, vector<int>(C, 0));
        
        using InnerElem=unordered_map<int, unordered_map<int, int>>;
        smm = vector<vector<InnerElem>>(R, vector<InnerElem>(C, InnerElem()));
        
        computeCSumsVSums(matrix);
        populateSmmSc(target);        
        
        
        // DP base cases:
        // cell (0, 0), upper row, left col
        dp[0][0] = matrix[0][0] == target ? 1 : 0;
        for (int c=1; c<C; c++) {
            dp[0][c] = dp[0][c-1] + sc[0][c];
        }
        for (int r=1; r<R; r++) {
            dp[r][0] = dp[r-1][0] + sc[r][0];
        }
        
        // DP.
        for (int r=1; r<R; r++) {
            for (int c=1; c<C; c++) {
                dp[r][c] = dp[r-1][c] + dp[r][c-1] - dp[r-1][c-1] + sc[r][c];
            }
        }
        return dp[R-1][C-1];
    }
};
