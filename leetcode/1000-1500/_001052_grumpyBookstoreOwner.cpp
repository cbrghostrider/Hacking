class Solution {
public:
    // O(n) time, O(1) space.
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int satisfy_no_ability = 0;
        for (int i=0; i<customers.size(); i++) {
            if (grumpy[i]) continue;
            satisfy_no_ability += customers[i];
        }
        
        // Sliding window, initial position
        int grumpy_affected=0;
        for (int i=0; i<minutes; i++) {
            grumpy_affected += grumpy[i] ? customers[i] : 0;
        }
        
        int most = grumpy_affected;
        for (int i=minutes; i<customers.size(); i++) {
            int fall_i = i-minutes;
            if (grumpy[fall_i]) { grumpy_affected -= customers[fall_i]; }
            if (grumpy[i]) {grumpy_affected += customers[i];}
            most = std::max(most, grumpy_affected);
        }
        
        int total = satisfy_no_ability + most;
        return total;
    }
};
