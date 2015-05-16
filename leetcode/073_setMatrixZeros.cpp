//using O(mn) time and O(1) space
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return; //ill-defined problem
        
        bool row0Zero = false, col0Zero = false;
        for (int i=0; i<matrix[0].size(); i++) { //check within 0th row
            if (matrix[0][i] == 0) row0Zero = true;
        }
        for (int i=0; i<matrix.size(); i++) {    //check within 0th column
            if (matrix[i][0] == 0) col0Zero = true;
        }
        for (int r=1; r<matrix.size(); r++) {
            for (int c=1; c<matrix[0].size(); c++) {
                if (matrix[r][c] == 0) matrix[0][c] = matrix[r][0] = 0;
            }
        }
        for (int r=1; r<matrix.size(); r++) {
            for (int c=1; c<matrix[0].size(); c++) {
                if (matrix[0][c] == 0 || matrix[r][0] == 0) matrix[r][c] = 0;
            }
        }
        for (int i=0; i<matrix[0].size(); i++) { 
            if (row0Zero) matrix[0][i] = 0;
        }
        for (int i=0; i<matrix.size(); i++) {    //check within 0th column
            if (col0Zero) matrix[i][0] = 0;
        }
    }
};
