class Solution {
    struct Point {
        double x=0;
        double y=0;
        bool operator==(const Point& rhs) const {
            return (x == rhs.x && y == rhs.y);
        }
        bool operator!=(const Point& rhs) const {
            return !(*this == rhs);
        }
    };
    
    double R=0;
    
    vector<Point> points;
    
    double getLength(const Point p1, const Point p2) {
        double xd = p1.x-p2.x;
        double yd = p1.y-p2.y;
        double len = std::sqrt(xd*xd + yd*yd);        
        return len;
    }
    
    //compute the chord, and then get the two centers
    vector<Point> getCenters(const Point& p1, const Point& p2) {
        double chord = getLength(p1, p2);
        double cby2 = chord/2;
        double perp_len = std::sqrt(R*R - cby2*cby2);
        
        // Get unit vector along chord.
        Point unit_vec  = {(p2.x-p1.x)/chord, (p2.y-p1.y)/chord};
        
        // Get chord mid point.
        Point chord_mid_pt = {p1.x+(p2.x-p1.x)/2, p1.y+(p2.y-p1.y)/2};
        
        // Scale along unit vector, to length of the perpendicular.
        Point vec = {perp_len * unit_vec.x, perp_len * unit_vec.y};
        
        // find perpendicular unit vector
        Point c1 = {-1* vec.y, vec.x};
        Point c2 = {vec.y,     -1*vec.x};
        
        // translate
        c1.x += chord_mid_pt.x; c2.x += chord_mid_pt.x;
        c1.y += chord_mid_pt.y; c2.y += chord_mid_pt.y;
        
        return {c1, c2};
    }
    
    int encapsulate(const Point& center) {
        int count=0;
        for (const Point& p : points) {
            double len = getLength(p, center);
            if (len <= R) {count++;}
        }
        return count;
    }

public:
    // O(n^3) time, O(n) space.
    //
    // Pick two points, treat them as the chord of the circle.
    // Find the center of the circle, given the chord and radius.
    // There are two potential centers in the plane.
    // Check how many points lie in the circle at that center.
    // Keep track of max.
    int numPoints(vector<vector<int>>& darts, int r) {        
        R=r;
        for (const vector<int>& dart : darts) {
            points.push_back({(double)dart[0], (double)dart[1]});
        }
        
        int best=0;
        for (int i=0; i<points.size(); i++) {
            for (int j=i+1; j<points.size(); j++) {
                Point p1 = points[i];
                Point p2 = points[j];
                if (p1 == p2) continue;
                if (getLength(p1, p2) > 2*R) continue;
                                
                vector<Point> centers = getCenters(p1, p2);
                
                int max_points=0;
                for (const Point& center : centers) {
                    int my_points = encapsulate(center);
                    max_points = std::max(max_points, my_points);
                }
                
                best = std::max(best, max_points);
            }
        }
        return best == 0 ? 1 : best;
    }
};
