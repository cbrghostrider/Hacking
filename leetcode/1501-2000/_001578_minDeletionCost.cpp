class Solution {
public:
    // Let min_cost(i) be the minimum cost of deletions up to index i.
    // Let k be the last retained index.
    // Recurrence:
    // min_cost(i) = 
    //   min_cost(i-1) ; if s[i] != s[k]
    //   min(cost[i] + min_cost(i-1), cost[k] + min_cost(k-1)) ; otherwise
    // O(n) time, O(n) space; can be optimized to O(1) space.
    int minCost(string s, vector<int>& cost) {
        if (s.size() <= 1) return 0;
        vector<int> mins(cost.size(), 0);
        int last_retained_i=0;
        
        // Base case.
        if (s[0] == s[1]) {
            mins[1] = std::min(cost[0], cost[1]);
            last_retained_i = (cost[0] >= cost[1] ? 0 : 1);
        } else {
            last_retained_i = 1;
        }

        // DP.
        for (int i=2; i<s.size(); i++) {
            if (s[i] != s[last_retained_i]) { 
                mins[i] = mins[i-1]; 
                last_retained_i = i;
                continue; 
            }
            int cost_delete_me = cost[i] + mins[i-1];
            int cost_delete_last_retained = cost[last_retained_i] + mins[i-1];
            if (cost_delete_me >= cost_delete_last_retained) {
                mins[i] = cost_delete_last_retained;
                last_retained_i = i;
            } else {
                mins[i] = cost_delete_me;
            }
        }
        return mins[cost.size()-1];
    }
};
