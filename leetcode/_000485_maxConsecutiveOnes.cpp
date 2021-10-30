class Solution {
    int max = 0;
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int curr_max = 0;
        for (int n : nums) {
            if (n == 1) {
                curr_max++;
            } else {
                if (curr_max > max) {max = curr_max;} 
                curr_max = 0;
            }
        }
        return (curr_max > max ? curr_max : max);
    }
};
