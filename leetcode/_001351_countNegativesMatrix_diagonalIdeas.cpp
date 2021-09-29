class Solution {
public:
    // Ideas for diagonal... some with pseudo code to try later.

    /////////////////////////////////////////////////////////////////////////////
    //
    // You NEED square matrices for this to work...
    // So break up the non-square matrix into -- square and non-square, recurse on smaller latter too.
    // 
    // Look diagonally for the last positive (binary search).
    // This subdivides the matrix into 4 parts. 
    // Top left sub-matrix is all positives, so can be eliminated (zero negatives).
    // Bottom right sub-matrix is all negatives, so can be trivially counted (p times q negatives).
    // Recurse in the top right and bottom left sub-matrices.
    // Termination condition is when you get a row matrix or a column matrix, in this case, do a binary search.
    //
    // Note that: column_index = x coordinate
    //            row_index = y coordinate
    
    int binarySearchRow(const vector<vector<int>>& grid, int row_index, int left, int right) {
        const vector<int>& row = grid[row_index];
        if (right - left <= 1) {
            int negatives = 0;
            if (row[left] < 0) negatives++;
            if (row[right] < 0 && left != right) negatives++;
            return negatives;
        }
        
        int mid = ((long long)left + right) / 2;
        if (row[mid-1] < 0) {
            return binarySearchRow(grid, row_index, left, mid-1) + 1 + (right - mid);
        } else if (row[mid] < 0) {
            return 1 + (right - mid);
        }
        return binarySearchRow(grid, row_index, mid+1, right);
    }
    
    int binarySearchColumn(const vector<vector<int>>& grid, int column_index, int top, int bottom) {
        if (bottom - top <= 1) {
            int negatives = 0;
            if (grid[top][column_index] < 0) negatives++;
            if (grid[bottom][column_index] < 0 && top != bottom) negatives++;
            return negatives;
        }
        
        int mid = ((long long)bottom + top) / 2;
        if (grid[mid-1][column_index] < 0) {
            return binarySearchColumn(grid, column_index, top, mid-1) + 1 + (bottom - mid);
        } else if (grid[mid][column_index] < 0) {
            return 1 + (bottom - mid);
        }
        return binarySearchColumn(grid, column_index, mid+1, bottom);
    }
    
    // This assumes that we are working on a square matrix.
    std::pair<int, int> findIndexLastNonNegativeDiagonal(const vector<vector<int>>& grid,
                                                         int tl_x, int tl_y,
                                                         int br_x, int br_y) {
        // Recursion termination, diagonal of 2 or less size.
        if (tl_x == br_x && tl_y == br_y) {
            return std::make_pair(tl_x, tl_y);
        }
        if (tl_x + 1 == br_x && tl_y + 1 == br_y) {
            if (grid[br_y][br_x] >= 0) {
                return std::make_pair(br_x, br_y);
            }
	    return std::make_pair(tl_x, tl_y);
        }
        
	int mid_x = ((long long)tl_x + br_x)/2;
	int mid_y = ((long long)tl_y + br_y)/2;

	// Check place on diagonal before and after mid, and return coordinate accordingly.
        // TODO
    }


    
    /////////////////////////////////////////////////////////////////////////////
    
    int countNegatives(vector<vector<int>>& grid) {
        return countNegativesMlogN(grid);
    }
};
