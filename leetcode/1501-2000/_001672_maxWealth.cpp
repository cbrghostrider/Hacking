class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int row_max = 0;
        for (int r=0; r<accounts.size(); r++) {
            int sum = 0;
            for (int c=0; c<accounts[r].size(); c++) {
                sum += accounts[r][c];
            }
            if (sum > row_max) row_max = sum;
        }
        return row_max;
    }
};
