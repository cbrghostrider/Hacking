//complexity is O(log m + log n) 
//where m = num rows, and n = num cols
class Solution {
    //return value indicates if element in matrix, if so, row indicates which row
    bool binSearchRow(vector<vector<int>>& matrix, int target, int rs, int re, int& row) {
        if (rs > re) return false;
        if (target < matrix[rs][0]) return false;                   //before start for first row
        if (target > matrix[re][matrix[0].size()-1]) return false;  //after end of last row
        if (target >= matrix[re][0]) { row = re; return true;}
        int mid = (rs+re)/2;
        int midplus = mid + 1;
        if (target > matrix[mid][matrix[0].size()-1] && target < matrix[midplus][0]) return false; 
        if (target <= matrix[mid][matrix[0].size()-1]) return (binSearchRow(matrix, target, rs, mid, row));
        return (binSearchRow(matrix, target, midplus, re, row));
    }
    
    //return value indicates if number within chosen row, and if so, which column
    bool binSearchCol(vector<vector<int>>& matrix, int target, int crow, int cs, int ce, int& col) {
        if (cs>ce) return false;
        if (cs == ce) {
            if (target != matrix[crow][cs]) return false;
            col = cs; 
            return true;
        }
        int mid = (cs + ce)/2;
        int midplus = mid+1;
        if (target > matrix[crow][mid] && target < matrix[crow][midplus]) return false;
        if (target <= matrix[crow][mid]) return binSearchCol(matrix, target, crow, cs, mid, col);
        return binSearchCol(matrix, target, crow, midplus, ce, col);
    }
    
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return false; //ill-formed input
        const int nrows = matrix.size();
        const int ncols = matrix[0].size();
        int row=0, col=0;
        
        //binary search on rows
        bool rowSearch = binSearchRow(matrix, target, 0, matrix.size()-1, row);
        if (!rowSearch) return false;
        
        //binary search on columns within chosen row
        return (binSearchCol(matrix, target, row, 0, matrix[0].size()-1, col));
    }
};
