class NumMatrix {
    // cumulative sum of rectangle from (0, 0) to (r, c).
    vector<vector<int>> csum;
    int R=0;
    int C=0;
public:
    // O(n^2) space, O(n^2) time.
    NumMatrix(vector<vector<int>>& matrix) {
        R = matrix.size();
        C = matrix[0].size();
        csum = vector<vector<int>>(R, vector<int>(C, 0));
        
        csum[0][0] = matrix[0][0];
        for (int ci=1; ci<C; ci++) {csum[0][ci] = csum[0][ci-1] + matrix[0][ci];}
        for (int ri=1; ri<R; ri++) {csum[ri][0] = csum[ri-1][0] + matrix[ri][0];}
        for (int ri=1; ri<R; ri++) {
            for (int ci=1; ci<C; ci++) {
                csum[ri][ci] = csum[ri-1][ci] + csum[ri][ci-1] - csum[ri-1][ci-1] + matrix[ri][ci];
            }
        }                                               
    }
    
    // O(1) time.
    int sumRegion(int row1, int col1, int row2, int col2) {
        int big_chunk  = csum[row2][col2];
        int top_chunk  = (row1 == 0 ? 0 : csum[row1-1][col2]);
        int left_chunk = (col1 == 0 ? 0 : csum[row2][col1-1]);
        int diag_chunk = (row1 == 0 || col1 == 0 ? 0 : csum[row1-1][col1-1]);
        return (big_chunk - top_chunk - left_chunk + diag_chunk);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
