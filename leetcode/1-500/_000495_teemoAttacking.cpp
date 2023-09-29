class Solution {
    int total = 0;
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (timeSeries.size() == 0) return 0;
        for (int i = 0; i < timeSeries.size() - 1; i++) {
            total += std::min(duration, timeSeries[i+1] - timeSeries[i]);
        }
        total += duration;
        return total;
    }
};
