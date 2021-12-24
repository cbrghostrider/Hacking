class Solution {
    // possible says whether it is possible to partition array nums[0..i]
    // into 2 arrays with difference of k
    //
    // possible(i, k) = possible(i-1, abs(k-nums[i])) || possible(i-1, k+nums[i])
    
    unordered_map<int, bool> cache;
    
    int signature(int i, int k) {
        return ((i << 16) | (k));
    }
    
    bool possible(const vector<int>& nums, int i, int k) {
        int sig = signature(i, k);
        if (cache.find(sig) != cache.end()) {
            return cache[sig];
        }
        if (i == 0) {
            cache[sig] = (nums[i] == k);
            return cache[sig];
        }
        
        bool possible1 = possible(nums, i-1, abs(k-nums[i]));
        bool possible2 = possible(nums, i-1, k+nums[i]);
        
        cache[sig] = (possible1 || possible2);
        return cache[sig];
    }
public:
    // Solution is functionally correct, but gets TLE for large inputs.
    bool canPartition(vector<int>& nums) {
        return possible(nums, nums.size()-1, 0);
    }
};
