class Solution {
public:
    // O(n) time, O(1) space.
    int maxProductDifference(vector<int>& nums) {
        int min1, min2, max1, max2;
        min1 = min2 = std::numeric_limits<int>::max();
        max1 = max2 = std::numeric_limits<int>::min();
        
        for (int n : nums) {
            if (n <= min1) {
                min2 = min1;
                min1 = n;
            } else if (n < min2) {
                min2 = n;
            }
            if (n >= max1) {
                max2 = max1;
                max1 = n;
            } else if (n > max2) {
                max2 = n;
            }
        }
        return (max2*max1 - min2*min1);
    }
};
