class Solution {
public:
    // O(n log n) time, O(1) space.
    // We want to send people to the "cheaper" city that we can fly them to.
    // We check the difference in costs of the ticket for a person i to each city (costs[i][0] - costs[i][1])
    // We sort on this.
    // The people at the start need to go to city A, and the people at the end to city B (in groups of 100).
    int twoCitySchedCost(vector<vector<int>>& costs) {
        std::sort(costs.begin(), costs.end(), 
                  [](const vector<int>& lhs, const vector<int>& rhs) -> bool {
            int cl = lhs[0] - lhs[1];
            int cr = rhs[0] - rhs[1];
            if (cl != cr) return cl < cr;
            return lhs[0] < rhs[0];
        });
        const int N = costs.size()/2;
        int total = 0;
        for (int i=0; i<N; i++) {
            total += costs[i][0] + costs[2*N-1-i][1];
        }
        return total;
    }
};
