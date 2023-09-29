class Solution {
    // given "num_indices" number of values that are equal
    // how many pairs can I form such that (i<j) 
    long long num_pairs(long long n) {        
        long long ret = ((n-1) * (n) / 2);        
        return ret;
    }
    unordered_map<int, int> freqs;

    void inc_freq(int val) {
        if (freqs.find(val) == freqs.end()) {
            freqs[val] = 1;
        } else {
            freqs[val]++;
        }
    }

public:
    long long countGood(vector<int>& nums, int k) {
        long long count=0;        

        // Initialize.
        int start=0, end=0;
        long long cur_pairs=0;  // keeps track of all current pairs that satisfy the condition
        freqs[nums[start]] = 1;

        // find subarrays which start from "start"        
        // Find end such that the interval between [start, end] contains at least k pairs with the condition        
        while (start < nums.size()) {
            
            // advance "end" enough that we get k pairs of indices with the condition
            while (end < nums.size() && cur_pairs < k) {                
                end++;
                if (end < nums.size()) {
                    cur_pairs -= num_pairs(freqs[nums[end]]);
                    inc_freq(nums[end]);
                    cur_pairs += num_pairs(freqs[nums[end]]);
                }
            }

            // broke out because finished
            if (end >= nums.size()) break;

            // all subarrays from [start, x] contribute to the count, where
            // x <- [end .... nums.size()-1]
            count += (nums.size() - end);

            // advance "start" enough that the condition with end doesn't hold anymore.
            while (start < end && cur_pairs >= k ) {
                cur_pairs -= num_pairs(freqs[nums[start]]);
                freqs[nums[start]]--;
                cur_pairs += num_pairs(freqs[nums[start]]);
                start++;
                if (cur_pairs >= k) {
                    count += (nums.size() - end);
                }
            }
        }
        return count;
    }
};
