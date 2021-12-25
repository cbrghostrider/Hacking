class Solution {
    int signature(int start, int end) {
        return ((start << 16) | (end));
    }
    
    unordered_map<int, int> cache;
    
    // finds len of max subarray, between start and end indices,
    // given the state of num_zeros, and num_ones
    int findBest(const vector<int>& nums, int start, int end, 
                 int num_zeros, int num_ones) {
        int sig = signature(start, end);
        if (cache.find(sig) != cache.end()) return cache[sig];
        
        if (start > end) {cache[sig] = -1; return -1;}
        
        if (num_zeros == num_ones) {
            cache[sig] = end-start+1;
            return cache[sig];
        }
                
        int ret = 0;  // the return value will be computed here
        
        // we need to shed some excess...
        bool drop_zeros = num_zeros > num_ones;
                        
        const int val_to_drop = drop_zeros ? 0 : 1;
        int& drop_ctr = drop_zeros ? num_zeros : num_ones;
        int& other_ctr = drop_zeros ? num_ones : num_zeros;
        
        if (nums[start] != val_to_drop && nums[end] != val_to_drop) { // both other value
            // Don't know which to drop, so try both.
            other_ctr--;
            int cand1 = findBest(nums, start+1, end, num_zeros, num_ones);
            int cand2 = findBest(nums, start, end-1, num_zeros, num_ones);
            ret = std::max(cand1, cand2);
        } else if (nums[start] == val_to_drop && nums[end] == val_to_drop) {  // both my value
            // Don't know which to drop, so try both.
            drop_ctr--;
            int cand1 = findBest(nums, start+1, end, num_zeros, num_ones);
            int cand2 = findBest(nums, start, end-1, num_zeros, num_ones);
            ret = std::max(cand1, cand2);            
        } else if (nums[start] == val_to_drop) {
            drop_ctr--;  // drop start
            ret = findBest(nums, start+1, end, num_zeros, num_ones);
        } else {  // nums[end] == val_to_drop
            drop_ctr--;  // drop end
            ret = findBest(nums, start, end-1, num_zeros, num_ones);
        }
        
        cache[sig] = ret;
        return ret;
    }
public:
    int findMaxLength(vector<int>& nums) {
       int zeros=0, ones=0;
        for (int n : nums) {if (n == 0) {zeros++;} else {ones++;} }       
        if (zeros == ones) return nums.size();
        int ret = findBest(nums, 0, nums.size()-1, zeros, ones);
        return (ret == -1 ? 0 : ret);
    }
};
