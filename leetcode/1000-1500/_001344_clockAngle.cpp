class Solution {
    unordered_map<int, int> angles = {
        {1, 30},  {2, 60},  {3, 90},  {4, 120},
        {5, 150}, {6, 180}, {7, 210}, {8, 240},
        {9, 270}, {10, 300}, {11, 330}, {12, 0}
    };
public:
    double angleClock(int hour, int minutes) {
        double min_angle = 1.0/60.0 * minutes * 360;
        double displacement = 0.5 * minutes;  // the hour hand moves this much forward from its normal position at hours
        double hour_angle = angles[hour] + displacement;
        double angle = std::abs(hour_angle - min_angle);
        return std::min(angle, 360 - angle);
    }
};
