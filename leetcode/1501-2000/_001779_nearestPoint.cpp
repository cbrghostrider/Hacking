class Solution {
public:
    // O(n) time, O(1) space.
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
        int ans_x = -1, ans_y = -1;
        int dist = std::numeric_limits<int>::max();
        int ind = -1;
        for (int i=0; i<points.size(); i++) {
            int xp = points[i][0];
            int yp = points[i][1];
            if (!(x == xp || y == yp)) continue;
            int d = std::abs(x - xp) + std::abs(y - yp);
            if (d < dist) {
                dist = d;
                ans_x = xp; ans_y = yp;
                ind = i;
            } else if (d == dist) {
                ; // smallest i already recorded
            }
        }
        return ind;
    }
};
