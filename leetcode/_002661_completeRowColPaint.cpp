struct Coord {
    int r=0;
    int c=0;
};
class Solution {
    int R, C;
    unordered_map<int, Coord> num_to_coord;
    vector<int> row_paint;
    vector<int> col_paint;
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        R = mat.size(); C = mat[0].size();
        row_paint = vector<int>(R, 0);
        col_paint = vector<int>(C, 0);
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                Coord crd = {r, c};
                num_to_coord[mat[r][c]] = crd;
            }
        }
        for (int i=0; i<arr.size(); i++) {
            Coord crd = num_to_coord[arr[i]];
            row_paint[crd.r]++;
            col_paint[crd.c]++;
            if (row_paint[crd.r] == C) return i;
            if (col_paint[crd.c] == R) return i;
        }
        // should not get here
        return -1;
    }
};
