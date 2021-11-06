class Solution {
public:
    int numDigits(int num) {
        int count = 0;
        while (num) {
            num /= 10;
            count++;
        }
        return count;
    }
    
    int findNumbers(vector<int>& nums) {
        int count = 0;
        for_each(nums.begin(), nums.end(), [&count, this](int num) {
            count += (numDigits(num) % 2 == 0 ? 1 : 0);
        });
        return count;
    }
};
