class Solution {
public:
    // length of a line segment
    double length(const vector<int>& a, const vector<int>& b) {
        return std::sqrt(((a[0] - b[0]) * (a[0] - b[0])) + ((a[1] - b[1]) * (a[1] - b[1])));
    }
    
    double areaTriangle(const vector<int>& a, const vector<int>& b, const vector<int>& c){
        // Using Heron's formula.
        double l1 = length(a, b), l2 = length(a, c), l3 = length(b, c);
        double s = (l1 + l2 + l3) / 2;
        return std::sqrt(s * (s-l1) * (s-l2) * (s-l3));
    }
    
    // O(n^3) algorithm
    double largestTriangleArea(vector<vector<int>>& points) {
        double ans = 0;
        for (int i=0; i<points.size(); i++) {
            for (int j=i+1; j<points.size(); j++) {
                for (int k=j+1; k<points.size(); k++) {
                    double area = areaTriangle(points[i], points[j], points[k]);
                    if (area > ans) ans = area;
                }
            }
        }
        return ans;
    }
};
