class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int sum = 0;
        const int LEN = mat.size();
        for (int i=0; i<LEN; i++) {
            sum += mat[i][i];
            sum += mat[LEN-1-i][i];
        }
        if ((LEN % 2) != 0) sum -= mat[LEN/2][LEN/2];
        return sum;
    }
};
