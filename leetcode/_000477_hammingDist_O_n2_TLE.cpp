class Solution {
    int popcount(uint32_t val) {
        uint32_t mask = 0x1;
        int sum=0;
        while (mask) {
            sum += (val & mask) ? 1 : 0;
            mask <<= 1;
        }
        return sum;
    }
public:
    // O(n^2) algorithm.
    int totalHammingDistance(vector<int>& nums) {
        int sum=0;
        for (int i=0; i<nums.size(); i++) {
            for (int j=i+1; j<nums.size(); j++) {
                sum += popcount(((uint32_t)nums[i]) ^ ((uint32_t)nums[j]));
            }
        }
        return sum;
    }
};
