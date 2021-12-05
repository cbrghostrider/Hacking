class Solution {
public:
    // let ssm(x, y, n) denote if we have a square submatrix with bottom right at (x, y) and of size n
    // Recurrence equation:
    // Let l = min(x, y)
    // ssm(x, y, n) 
    //    = false ; if matrix(x,y) is 0
    //    = false ; if (n > l || x == 0 || y == 0 || n == 0)
    //    = false ; if ssm(x-1, y-1, n-1) is false
    //    = false ; if ssm(x-1, y, n-1) is false
    //    = false ; if ssm(x, y-1, n-1) is false
    //    = true  ; otherwise
    //
    // O(n^3) algorithm.
    int countSquares2(vector<vector<int>>& matrix) {
        const int X = matrix.size(), Y=matrix[0].size();
        vector<vector<vector<bool>>> cache(X, vector<vector<bool>>(Y, vector<bool>(std::min(X,Y), false)));
         
        int count=0;
        for (int x=0; x<X; x++) {
            for (int y=0; y<Y; y++) {
                bool possible = (matrix[x][y] == 1);
                int l = std::min(x, y) + 1;
                cache[x][y][1] = possible;
                if (possible) {
                    count++;
                }
                for (int n=2; n<=l; n++) {
                    possible = possible && x!=0 && y!=0 && 
                        cache[x-1][y-1][n-1] && cache[x-1][y][n-1] && cache[x][y-1][n-1];
                    cache[x][y][n] = possible;
                    if (possible) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
    
    // instead of storing bool, store how many submatrices are possible at that place.
    // then looking at top, left, and top-left of current position, we can determine how many
    // are possible for the current position
    // O(n^2) solution.
    int countSquares(vector<vector<int>>& matrix) {
        const int X = matrix.size(), Y=matrix[0].size();
        vector<vector<int>> cache(X, vector<int>(Y, 0));
         
        int count=0;
        for (int x=0; x<X; x++) {
            for (int y=0; y<Y; y++) {
                if (x == 0 || y == 0) {
                    cache[x][y] = matrix[x][y];
                    if (cache[x][y]) {
                        count++;
                    }
                    continue;
                } else if (matrix[x][y] == 0) {
                    cache[x][y] = 0;
                    continue;
                }
                cache[x][y] = std::min(std::min(cache[x-1][y], cache[x][y-1]), cache[x-1][y-1]) + 1;
                if (cache[x][y]) {
                    count += cache[x][y];
                }
            }
        }
        return count;
    }
};


