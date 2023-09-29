class Solution {
public:
    // Recurrence:
    // cost(i) = min(c1, c7, c30) where
    //   c1 = 1-day-cost + cost(i+1)
    //   c7 = 7-day-cost + cost(x) ... where x is 7+ days past i
    //   c30 = 30-day-cost + cost(y) ... where y is 30+ days past i
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        if (days.size() == 0) return 0;
        std::sort(days.begin(), days.end());
        vector<int> optimum(days.size(), 0);
        const int N=days.size();
        for (int i=N-1; i>=0; i--) {
            int iafter7 = i, iafter30 = i;
            for (; iafter7<N; iafter7++) {if (days[iafter7] >= days[i] + 7) {break;}}
            for (; iafter30<N; iafter30++) {if (days[iafter30] >= days[i] + 30) {break;}}
            int c1 = costs[0] + (i+1 == N ? 0 : optimum[i+1]);
            int c7 = costs[1] + (iafter7 == N ? 0 : optimum[iafter7]);
            int c30 = costs[2] + (iafter30 == N ? 0 : optimum[iafter30]);
            optimum[i] = std::min(c1, std::min(c7, c30));
        }
        return optimum[0];
    }
};
