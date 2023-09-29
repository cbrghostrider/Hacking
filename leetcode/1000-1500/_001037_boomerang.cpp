class Solution {
public:
    bool isBoomerang(vector<vector<int>>& points) {
        if (points[0][0] == points[1][0] && points[0][1] == points[1][1]) return false;
        if (points[0][0] == points[2][0] && points[0][1] == points[2][1]) return false;
        if (points[2][0] == points[1][0] && points[2][1] == points[1][1]) return false;
        
        // first check for slope infinity case
        bool is_vert = (points[0][0] == points[1][0] && points[1][0] == points[2][0]);
        if (is_vert) {return false;}
        
        // then check slopes
        double slope01 = ((double)(points[0][1]-points[1][1]))/(points[0][0]-points[1][0]);
        double slope12 = ((double)(points[1][1]-points[2][1]))/(points[1][0]-points[2][0]);
        return (slope01 != slope12);
    }
};
