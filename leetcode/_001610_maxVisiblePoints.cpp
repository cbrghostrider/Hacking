// Currently the O(nlogn) solution has a bug for some medium sized input.
//   But once that gets debugged, it should function for large inputs too.
// The O(n^2) solution works, but gets TLE for large inputs.

class Solution {
    const double PI = 3.14159265;

    struct Coord {
        int x=0;
        int y=0;
        bool operator==(const Coord& rhs) {
            return x == rhs.x && y == rhs.y;
        }
    };
    
    vector<double> slopes;
    Coord origin;
    
    // returns slope of the line in radians [0, 2*PI]
    double slope(Coord from, Coord to) {
        double delta_x = to.x - from.x;
        double delta_y = to.y - from.y;
        double slope = std::atan2(delta_y, delta_x);
        if (slope < 0) {slope += 2*PI;}
        return slope;
    }
    
    // Says whether point "check" is visible in current POV.
    // current POV is determined by the cone formed of size "angle"
    // with segment [origin, edge_point] as rightmost edge of cone
    bool isVisible(int check_index, int edge_index, double angle) {
        if (check_index == edge_index) return true;
        double slope_edge  = slopes[edge_index];
        double slope_check = slopes[check_index];
        return isVisibleSlopes(slope_edge, slope_check, angle);
    }
    
    // The version of isVisible that directly works with slopes
    bool isVisibleSlopes(double slope_edge, double slope_check, double angle) {
        if (slope_edge == slope_check) return true;
        
        double sweep_value = slope_edge + angle;
        if (sweep_value >= 2*PI) {sweep_value -= 2*PI;}
        
        if (sweep_value >= slope_edge) {  // sweep didn't cross x=0 pointing right
            return (slope_edge <= slope_check && slope_check <= sweep_value);
        }
        bool cond1 = (slope_edge <= slope_check && slope_check <= 2*PI);
        bool cond2 = (0 <= slope_check && slope_check <= sweep_value);
        return (cond1 || cond2);
    }
    
public:
    // O(n ^2) algorithm.
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        double angle_rads = angle * PI / 180.0;
        origin = {location[0], location[1]};
        
        int origin_count=0;
        for (int i=0; i<points.size(); i++) {
            Coord coord = {points[i][0], points[i][1]};
            if (coord == origin) {
                origin_count++; 
                slopes.push_back(-10000); // invalid, won't be used
                continue;
            }
            slopes.push_back(slope(origin, coord));
        }
        
        int max=0;
        for (int i=0; i<points.size(); i++) {
            Coord edge = {points[i][0], points[i][1]};
            if (edge == origin) {continue;}
            int count_e = 0;
            for (int j=0; j<points.size(); j++) {
                Coord coord = {points[j][0], points[j][1]};
                if (coord == origin) {continue;}
                if (isVisible(j, i, angle_rads)) {count_e++;}
            }
            if (max < count_e) {max = count_e;}
        }
        return max+origin_count;
    }
    
    // O(n log n) time.
    int visiblePoints_nlogn(vector<vector<int>>& points, int angle, vector<int>& location) {
        double angle_rads = angle * PI / 180.0;
        origin = {location[0], location[1]};
        
        int origin_count=0;
        for (int i=0; i<points.size(); i++) {
            Coord coord = {points[i][0], points[i][1]};
            if (coord == origin) {
                origin_count++; 
                continue;
            }
            slopes.push_back(slope(origin, coord));
        }
        
        std::sort(slopes.begin(), slopes.end());
        
        int max=0;
        int edge_ptr=0, check_ptr=0;
        int npoints=0;  // keeps track of points in current window
        unordered_map<int, int> counts;
        while (edge_ptr < slopes.size()) {
            while (check_ptr < slopes.size() && 
                   isVisibleSlopes(slopes[edge_ptr], slopes[check_ptr], angle_rads)) {
                check_ptr++;
                npoints++;
            }
            if (check_ptr == slopes.size()) {  // we may have to wrap around and check
                check_ptr=0;
                while (check_ptr < edge_ptr && 
                       isVisibleSlopes(slopes[edge_ptr], slopes[check_ptr], angle_rads)) {
                    check_ptr++;
                    npoints++;
                }
            }
            counts[edge_ptr] = npoints;
            if (npoints > max) {max = npoints;}
            
            // if everything is visible, just break out
            if (isVisibleSlopes(slopes[edge_ptr], slopes[check_ptr], angle_rads)) {break;}
            
            while (edge_ptr < slopes.size() && 
                   !isVisibleSlopes(slopes[edge_ptr], slopes[check_ptr], angle_rads)) {
                edge_ptr++;
                npoints--;
            }
        }
        return (max+origin_count);
    }
};
