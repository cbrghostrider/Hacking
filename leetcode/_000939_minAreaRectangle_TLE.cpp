class Solution {
    // For all pairs of points (a, b), consider those that have same y-coord
    // store those 2 points as a pair in a map, where key = (x coord of left, distance between points)
    // now all pairs of points mapping to the same key can be checked for area
    
    string signature(int x_left, int distance) {
        return (std::to_string(x_left) + "-" + std::to_string(distance));
    }
    
    struct Point {
        int x=0;
        int y=0;
    };
    
public:
    // Functionally correct, but gets TLE for large n (~500).
    int minAreaRect(vector<vector<int>>& points) {
        unordered_map<string, vector<pair<Point, Point>>> check_map;
        
        for (int i=0; i<points.size(); i++) {
            Point a = {points[i][0], points[i][1]};
            for (int j=i+1; j<points.size(); j++) {
                Point b = {points[j][0], points[j][1]};
                if (a.y != b.y) continue;
                int left_x = std::min(a.x, b.x);
                int distance = std::abs(a.x - b.x);
                string sig = signature(left_x, distance);
                if (a.x > b.x) {check_map[sig].push_back({b, a});}
                else {check_map[sig].push_back({a, b});}
            }
        }
        
        int min_area = std::numeric_limits<int>::max();
        for (const auto& kv : check_map) {
            const vector<pair<Point, Point>>& vec = kv.second;
            for (int i=0; i<vec.size(); i++) {
                for (int j=i+1; j<vec.size(); j++) {
                    Point a_1 = vec[i].first; Point b_1 = vec[i].second;  // 1st line segment
                    Point a_2 = vec[j].first; Point b_2 = vec[j].second;  // 2nd line segment
                    if (a_1.y == a_2.y) continue;  // delta_y is zero, so not a rectangle at all
                    int delta_x = std::abs(a_1.x - b_1.x);
                    int delta_y = std::abs(a_1.y - a_2.y);
                    int area = delta_x * delta_y;
                    if (area < min_area) {min_area = area;}
                }
            }
        }
        return min_area == std::numeric_limits<int>::max() ? 0 : min_area;
    }
};
