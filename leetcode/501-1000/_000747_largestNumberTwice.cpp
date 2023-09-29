class Solution {
public:
    int dominantIndex(vector<int>& nums) {
        if (nums.size() == 0) return -1;
        if (nums.size() == 1) return 0;
        
        int index = 0;
        int largest = std::numeric_limits<int>::min();
        for (int i=0; i<nums.size(); i++) {
            if (nums[i] > largest) {
                largest = nums[i];
                index = i;
            }
        }
        for (int n: nums) {
            if (n == largest) continue;
            if (2 * n > largest) return -1;
        }
        return index;
    }
};
