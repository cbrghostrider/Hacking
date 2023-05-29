class Solution {
    int R, C;
    vector<vector<int>> ans;

    void compute_row(const vector<vector<int>>& heights, int r) {
        // (index, height): mono decreasing stack
        vector<pair<int, int>> mono;

        for (int c=0; c<C; c++) {
            int greatest=0;  // to avoid contributing to adjacent dups
            while (!mono.empty() && mono.back().second < heights[r][c]) {
                // The new guy contributes to each guy on TOS
                auto tt = mono.back();
                mono.pop_back();
                if (heights[r][tt.first] > greatest) {
                    ans[r][tt.first]++;
                    greatest = heights[r][tt.first];
                }
            }

            if (!mono.empty()) {
                // New guy also contributes to this taller dude on his left.
                ans[r][mono.back().first]++;
            }

            // put new guy on TOS
            mono.push_back(make_pair(c, heights[r][c]));
        }
    }
    void compute_col(const vector<vector<int>>& heights, int c) {
        // (index, height): mono decreasing stack
        vector<pair<int, int>> mono;

        for (int r=0; r<R; r++) {
            int greatest=0;  // to avoid contributing to adjacent dups
            while (!mono.empty() && mono.back().second < heights[r][c]) {
                // The new guy contributes to each guy on TOS
                auto tt = mono.back();
                mono.pop_back();
                if (heights[tt.first][c] > greatest) {
                    ans[tt.first][c]++;
                    greatest = heights[tt.first][c];
                }
            }

            if (!mono.empty()) {
                // New guy also contributes to this taller dude on his left.
                ans[mono.back().first][c]++;
            }

            // put new guy on TOS
            mono.push_back(make_pair(r, heights[r][c]));
        }       
    }
public:
    vector<vector<int>> seePeople(vector<vector<int>>& heights) {
        R=heights.size(); C=heights[0].size();
        ans = vector<vector<int>>(R, vector<int>(C, 0));

        for (int r=0; r<R; r++) {
            compute_row(heights, r);
        }
        for (int c=0; c<C; c++) {
            compute_col(heights, c);
        }
        return ans;
    }
};
