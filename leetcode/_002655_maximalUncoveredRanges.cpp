class Solution {
    struct Info {
        bool is_start = false;
        int val = 0;
    };
public:
    vector<vector<int>> findMaximalUncoveredRanges(int n, vector<vector<int>>& ranges) {
        vector<Info> points;
        for (const auto& r : ranges) {
            points.push_back({true, r[0]});
            points.push_back({false, r[1]});
        }
        std::sort(points.begin(), points.end(), [](const Info& lhs, const Info& rhs) -> bool {
            if (lhs.val < rhs.val) return true;
            if (lhs.val > rhs.val) return false;
            if (lhs.is_start == rhs.is_start) return false;
            if (lhs.is_start == true) return true;
            return false;
        });
        vector<vector<int>> result;
        int crd = 0;
        int overlaps = 0;
        for (const auto& point : points) {
            if (point.is_start) {
                if (overlaps == 0) {
                    if (crd <= point.val-1) {
                        result.push_back({crd, point.val-1});
                    } 
                }
                overlaps++;
            } else {
                overlaps--;
                if (overlaps == 0) {
                    crd = point.val+1;
                }
            }
        }
        if (crd <= n-1) {
            result.push_back({crd, n-1});
        }  
        return result;
    }
};
