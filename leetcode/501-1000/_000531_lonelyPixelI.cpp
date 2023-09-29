class Solution {
public:
    // O(m*n) time, O(n) space.
    int findLonelyPixel(vector<vector<char>>& picture) {
        int ans=0;
        const int R=picture.size();
        const int C=picture[0].size();
        
        vector<int> count_for_row(R, 0);
        for (int r=0; r<R; r++) {
            for (int c=0; c<C; c++) {
                if (picture[r][c] == 'B') {
                    count_for_row[r]++;
                }
            }
        }
        
        for (int c=0; c<C; c++) {
            int count=0;
            std::pair<int, int> coord;
            for (int r=0; r<R; r++) {
                if (picture[r][c] == 'B') {
                    count++;
                    coord = make_pair(r, c);
                }
            }
            if (count == 1 && count_for_row[coord.first] == 1) {  // 1 in column c 1 in corresponding row
                ans++;
            }
        }
        return ans;
    }
};
