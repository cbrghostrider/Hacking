class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int num_5 = 0, num_10 = 0, num_20 = 0;
        for (int bill : bills) {
            // Charge.
            int change = bill - 5;
            
            // Process change.
            if (change == 5) {
                if (num_5 == 0) return false;
                num_5--;
            } else if (change == 10) {
                if (num_10 > 0) {
                    num_10--;
                } else if (num_5 >= 2) {
                    num_5 -= 2;
                } else {
                    return false;
                }
            } else if (change == 15) {
                if (num_10 > 0 && num_5 > 0) {
                    num_10--; num_5--;
                } else if (num_5 >= 3) {
                    num_5 -= 3;
                } else {
                    return false;
                }
            }
            
            // Update bills.
            if (bill == 5) num_5++;
            if (bill == 10) num_10++;
            if (bill == 20) num_20++;
        }
        return true;
    }
};
