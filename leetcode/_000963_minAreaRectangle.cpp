struct Point {
    int x=0;
    int y=0;
    bool operator==(const Point& rhs) const {
        return (x == rhs.x && y == rhs.y);
    }
    string toString() const {
        return "(" + to_string(x) + "," + to_string(y) + ");";
    }
};
    
struct Slope {
    double m=0.0;
    bool parallel_to_y = false;
    string toString() const {
        if (parallel_to_y) {return "parallel_to_y;";}
        return std::to_string(m) + ";";
    }
};

// For every pair of points, records the slope and distance
struct Info {
    Point a;
    Point b;
    Slope slope;
    double distance=0.0;
    
    string sig() const {
        return slope.toString() + to_string(distance) + ";";
    }
};

Slope getSlope(const Point& a, const Point& b) {
    if (a.x == b.x) {
        return {0.0, true};
    }
    double m = std::atan2(a.y-b.y, a.x-b.x);
    if (m < 0) {
        double PI = atan(1)*4;
        m += PI;
    }
    return {m, false};
}

double getDistance(const Point& a, const Point& b) {
    if (a == b) return 0.0;
    double sum_sq = std::pow((a.x-b.x), 2) + std::pow((a.y-b.y), 2);
    return std::sqrt(sum_sq);
}

class Solution {    
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        unordered_map<string, vector<Info>> info_map_1;
        
        for (int i=0; i<points.size(); i++) {
            Point a = {points[i][0], points[i][1]};
            for (int j=i+1; j<points.size(); j++) {
                Point b = {points[j][0], points[j][1]};
                Slope sl = getSlope(a, b);
                double dist = getDistance(a, b);
                Info info = {a, b, sl, dist}; 
                info_map_1[info.sig()].push_back(info);
            }
        }
        
        double min_area = std::numeric_limits<double>::max();
        for (const auto& kv : info_map_1) {
            const vector<Info>& vec = kv.second;
            for (int i=0; i<vec.size(); i++) {
                Info info_i = vec[i];
                for (int j=i+1; j<vec.size(); j++) {
                    Info info_j = vec[j];
                    
                    // At this point we have (info_i.a, info_i.b) and (info_j.a, info_j.b) segments
                    // These are both having the same slope, and same size segments.
                    
                    // We need to check if the 4 points involved have the *other* 2 segments with
                    // the same properties (same slope, same distance)
                    // Finally the 2 diagonal segments have to be same distance as well.
                    // i.e. in a rectangle, the two opposite sides have same slope and same distance as each other.
                    // the two diagonals also have same distance as each other.
                    
                    double dist_ia_ja = getDistance(info_i.a, info_j.a);
                    double dist_ia_jb = getDistance(info_i.a, info_j.b);
                    double dist_ib_ja = getDistance(info_i.b, info_j.a);
                    double dist_ib_jb = getDistance(info_i.b, info_j.b);

                    // If both these comparisons are true, we in fact have a rectangle
                    bool cmp1 = dist_ia_ja == dist_ib_jb;
                    bool cmp2 = dist_ia_jb == dist_ib_ja;
                    
                    if (cmp1 && cmp2) {
                        double dist_other = std::min(dist_ia_ja, dist_ia_jb);
                        double area = dist_other * info_i.distance;
                        if (area < min_area) {
                            min_area = area;
                        }
                    }
                }
            }
        }
        return (min_area == std::numeric_limits<double>::max() ? 0 : min_area);
    }
};
