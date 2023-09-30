class Solution {
public:

    // Input is a sorted array.
    // Returns number of pairs of indices, i !=j, whose sum <= val;
    long long numSumsLEq(const vector<int>& nums, int val) {
        int hi=nums.size()-1;
        long long count=0;
        for (int lo=0; lo < nums.size() && lo < hi; lo++) {
            while (lo < hi && nums[lo]+nums[hi] > val) {
                hi--;
            }
            if (lo < hi) {
                count += hi-lo;
            }
        }
        return count;
    }

    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        std::sort(nums.begin(), nums.end());
        return numSumsLEq(nums, upper) - numSumsLEq(nums, lower-1);
    }
   
};
