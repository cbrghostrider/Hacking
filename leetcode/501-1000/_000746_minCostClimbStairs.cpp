class Solution {
public:
    
    // O(n) space, O(n) time
    int minCostClimbingStairs2(vector<int>& cost) {
        if (cost.size() == 0) return 0;
        if (cost.size() == 1) return 0;
        if (cost.size() == 2) return std::min(cost[0], cost[1]);
        
        // If I started on step i, what minimum payment would get me to the top.
        vector<int> payment(cost.size(), 0);  
        
        for (int i=cost.size()-1; i>=0; i--) {
            int pay = cost[i];
            int step_one = (i == cost.size()-1) ? 0 : payment[i+1];
            int step_two = (i >= cost.size() - 2) ? 0 : payment[i+2];
            payment[i] = pay + std::min(step_one, step_two);
        }
        return std::min(payment[0], payment[1]);
    }
    
    // O(1) space, O(n) time
    // Don't need to keep entire payment array.
    int minCostClimbingStairs(vector<int>& cost) {
        if (cost.size() == 0) return 0;
        if (cost.size() == 1) return 0;
        if (cost.size() == 2) return std::min(cost[0], cost[1]);
        
        // If I started on step i, what minimum payment would get me to the top.
        int payment_two = 0, payment_one = 0;  
        
        for (int i=cost.size()-1; i>=0; i--) {
            int pay = cost[i];
            int step_one = (i == cost.size()-1) ? 0 : payment_one;
            int step_two = (i >= cost.size() - 2) ? 0 : payment_two;
            int new_payment = pay + std::min(step_one, step_two);
            payment_two = payment_one;
            payment_one = new_payment;
        }
        return std::min(payment_one, payment_two);
    }
};
