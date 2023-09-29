class Solution {
public:
    // O(n log n) due to sorting.
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        std::sort(points.begin(), points.end(), 
                  [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            double dist_lhs = std::sqrt(lhs[0]*lhs[0] + lhs[1]*lhs[1]);
            double dist_rhs = std::sqrt(rhs[0]*rhs[0] + rhs[1]*rhs[1]);
            return (dist_lhs < dist_rhs);
        });
        points.erase(points.begin()+k, points.end());
        return points;
    }
};
