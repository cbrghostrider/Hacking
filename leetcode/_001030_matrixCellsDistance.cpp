class Solution {
public:
    vector<vector<int>> allCellsDistOrder(int rows, int cols, int rCenter, int cCenter) {
        vector<vector<int>> coords;
        for (int r=0; r<rows; r++) {
            for (int c=0; c<cols; c++) {
                coords.push_back({r, c});
            }
        }
        std::sort(coords.begin(), coords.end(), 
                    [rCenter, cCenter](const vector<int>& left, const vector<int>& right) -> bool {
            int d_left = std::abs(left[0] - rCenter) + std::abs(left[1] - cCenter);
            int d_right = std::abs(right[0] - rCenter) + std::abs(right[1] - cCenter);
            return d_left < d_right;
        });
        return coords;
    }
};
