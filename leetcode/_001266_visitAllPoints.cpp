class Solution {
public:
    int calcCost(const vector<vector<int>>& points, int from, int to) {
        int delta_x = std::abs(points[from][0] - points[to][0]);
        int delta_y = std::abs(points[from][1] - points[to][1]);
        return std::max(delta_x, delta_y);
    }
    
    // O(n) time, O(1) space.
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int time = 0;
        for (int i=1; i<points.size(); i++) {
            time += calcCost(points, i-1, i);
        }
        return time;
    }
};
