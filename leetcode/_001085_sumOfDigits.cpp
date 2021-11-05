class Solution {
public:
    int sumOfDigits(vector<int>& nums) {
        int min = nums[0];
        for (int n : nums) {if (n < min) min = n;}
        int sum_digits = 0;
        while (min) {
            sum_digits += (min % 10);
            min = min/10;
        }
        return (sum_digits % 2 != 0 ? 0 : 1);
    }
};
