class Solution {
    int R = 0;
    int C = 0;
    bool isDiagonalToeplitz(const vector<vector<int>>& mat, int r, int c) {
        const int elem = mat[r][c];
        while (r < R && c < C) {
            if (elem != mat[r][c]) return false;
            r++; c++;
        }
        return true;
    }
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        R = matrix.size();
        C = matrix[0].size();
        
        for (int r=0; r<R; r++) {
            if (!isDiagonalToeplitz(matrix, r, 0)) return false;
        }
        for (int c=0; c<C; c++) {
            if (!isDiagonalToeplitz(matrix, 0, c)) return false;
        }
        return true;
    }
};
