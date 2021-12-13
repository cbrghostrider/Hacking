//
// Unfortunately I solved for a FAR more complicated case, 
// where the inputs p and q are DOUBLE valued instead of
// being INTEGER valued
//
// The solution becomes much simpler with integer valued
// due to the math involved.
// Oh well...
//

class Solution {    
    // the equations of the 4 walls, as expressed in ax + by + c = 0 format are:
    struct Line {
        double a=0;
        double b=0;
        double c=0;
    };
    enum Wall {TOP, BOTTOM, LEFT, RIGHT};
    
    struct Point {
        double x=0;
        double y=0;
    };
    
    double P=-1;  // the length of each wall
    int ans=-1;  // will eventually contain 0, 1, or 2
    
    // All these functions are needed because double values may be a bit inexact.
    double threshold = 0.0001;
    bool areSame(Point a, Point b) {
        bool same_x = (a.x >= (b.x - threshold) && a.x <= (b.x + threshold));
        bool same_y = (a.y >= (b.y - threshold) && a.y <= (b.y + threshold));
        return same_x && same_y;
    }
    bool isVal(double check, double val) {
        return (check <= (val + threshold) && check >= (val - threshold));
    }
    bool isZero(double check) {
        return isVal(check, 0.0);
    }
    bool isLen(double check) {
        return isVal(check, P);
    }
    bool isCorner(Point check) {
        if (isLen(check.x) && isZero(check.y)) {
            ans = 0;
            return true;
        } else if (isLen(check.x) && isLen(check.y)) {
            ans = 1;
            return true;
        } else if (isZero(check.x) && isLen(check.y)) {
            ans = 2;
            return true;
        }
        // We don't need to check for (0, 0), as per problem guidelines.
        return false;
    }
    // Makes sure that the found point is within the walls.
    bool withinBounds(Point check) {
        bool bounded_x = (check.x >= (0 - threshold) && check.x <= (P + threshold));
        bool bounded_y = (check.y >= (0 - threshold) && check.y <= (P + threshold));
        return bounded_x && bounded_y;
    }    
    
    Point getIntersection(Line l1, Line l2) {
        double x_num = l1.b*l2.c - l2.b*l1.c;
        double y_num = l1.c*l2.a - l2.c*l1.a;
        double den   = l1.a*l2.b - l2.a*l1.b;
        // Assuming no div by 0.
        return {x_num/den, y_num/den};
    }
    
    Line getRay(Point last_point, Point new_point, Wall new_wall) {
        Point from = new_point; 
        // The angle of incidence is the same as the angle of reflection.
        // We want to compute "a new new point" along the reflected ray
        // this isn't necessarily the point on the next wall within bounds, 
        // but we need it to compute the equation for the reflected ray
        Point new_new_point;
        double delta_x = new_point.x - last_point.x;
        double delta_y = new_point.y - last_point.y;
        if (new_wall == RIGHT || new_wall == LEFT) {
            new_new_point = {last_point.x, last_point.y + 2*delta_y};
        } else {
            new_new_point = {last_point.x + 2*delta_x, last_point.y};
        }
        Point to = new_new_point;
        
        double m = (to.y - from.y) / (to.x - from.x);
        double c = to.y - m*to.x;
        return Line({-1*m, 1, -1*c});
        
    }
public:

    int mirrorReflection(int p, int q) {      
        P = p;
        Line top_wall    = {0, 1, -1*P};
        Line bottom_wall = {0, 1,  0};
        Line left_wall   = {1, 0,  0};
        Line right_wall  = {1, 0, -1*P};
        // y = mx + c
        // or (-mx + y - c =0)
        // m = q/p
        // c = 0 (y-intercept)
        double minus_m = -1 * ((double)q) / ((double)p);
        Line ray({minus_m, 1, 0});
        
        // The last point of intersection.
        Point last({0, 0});
        
        // The algorithm is as follows:
        // We find where the current ray intersects all 4 walls.
        // then we take only those points that lie between the wall bounds
        // this should give us 2 points, one of which is the last point
        // we check if the next point is a corner, if so we found it.
        // else we compute the new ray equation using incidence/reflection rules
        // and continue trying to find the corner via next reflection
        while (1) {
            Point t_n = getIntersection(top_wall, ray);
            Point b_n = getIntersection(bottom_wall, ray);
            Point l_n = getIntersection(left_wall, ray);
            Point r_n = getIntersection(right_wall, ray);
            
            Point new_point;
            Wall new_wall;
            if (!areSame(t_n, last) && withinBounds(t_n)) {new_point = t_n; new_wall = TOP;}
            if (!areSame(b_n, last) && withinBounds(b_n)) {new_point = b_n; new_wall = BOTTOM;}
            if (!areSame(l_n, last) && withinBounds(l_n)) {new_point = l_n; new_wall = LEFT;}
            if (!areSame(r_n, last) && withinBounds(r_n)) {new_point = r_n; new_wall = RIGHT;}
            
            if (isCorner(new_point)) {break;}
            
            ray = getRay(last, new_point, new_wall);
            last = new_point;
        }
        return ans;
    }
};
