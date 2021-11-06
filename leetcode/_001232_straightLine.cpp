class Solution {
    double THRESHOLD = 0.00001;
    
    // Returns true if the slope is vertical.
    // Only writes slope if not vertical.
    bool calcSlope(const vector<int>& p1, const vector<int>& p2, double& slope) {
        double num = p1[1] - p2[1];
        int den = p1[0] - p2[0];
        if (den != 0) {
            slope = num/den;
        }        
        return den != 0;
    }
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        double slope = 0;
        bool vert = calcSlope(coordinates[0], coordinates[1], slope);
        
        for (int i=1; i<coordinates.size(); i++) {
            double s = 0;
            bool v = calcSlope(coordinates[i-1], coordinates[i], s);
            if ((v && !vert) || (!v && vert)) return false;
            if (std::abs(slope - s) > THRESHOLD) return false;
        }
        return true;
    }
};
