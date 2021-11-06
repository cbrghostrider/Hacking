class Solution {
public:
    // O(m*n) time, O(m + n) space.    
    int oddCells(int m, int n, vector<vector<int>>& indices) {
        vector<int> row_incs(m, 0);
        vector<int> col_incs(n, 0);
        for (const vector<int>& rc : indices) {
            row_incs[rc[0]]++;
            col_incs[rc[1]]++;
        }
        int odds = 0;
        for (int r : row_incs) {
            for (int c : col_incs) {
                if ((r+c) % 2 != 0) odds++;
            }
        }
        return odds;
    }
};
