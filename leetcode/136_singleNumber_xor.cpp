class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int xorv = 0;
        for (int& num : nums) xorv ^= num;
        return xorv;
    }
};
