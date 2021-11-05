class Solution {
public:
    int getPoints(int cals, int lower, int upper) {
        if (cals < lower) return -1;
        if (cals > upper) return 1;
        return 0;
    }
    
    int dietPlanPerformance(vector<int>& calories, int k, int lower, int upper) {
        int sum = 0;
        for (int i=0; i<k; i++) { sum += calories[i]; }
        int points = getPoints(sum, lower, upper);
        for (int i=k; i<calories.size(); i++) {
            sum += calories[i] - calories[i-k];
            points += getPoints(sum, lower, upper);
        }
        return points;
    }
};
