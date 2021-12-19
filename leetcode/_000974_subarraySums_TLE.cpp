class Solution {
    
public:
    // O(n^2) time, O(n) space.
    // TLE.
    int subarraysDivByK_(vector<int>& nums, int k) {
        vector<int> cumu_sum(nums.size(), 0);
        int sum=0;
        for (int i=0; i<nums.size(); i++) {
            sum += nums[i];
            cumu_sum[i] = sum;
        }
        
        int count=0;
        for (int i=0;i<nums.size(); i++) {
            for (int j=i; j<nums.size(); j++) {
                int val = cumu_sum[j] - cumu_sum[i] + nums[i];
                if (val % k == 0) count++;
            }
        }
        return count;
    }
    
    //
    // This one doesn't work yet!
    //
    int subarraysDivByK(vector<int>& nums, int k) {
        vector<int> csum(nums.size(), 0);
        
        // (val, count)
        // how many prior indices rem up to val.
        unordered_map<int, int> rem_counts;
        
        int sum=0, count=0, max_neg=0;
        for (int i=0; i<nums.size(); i++) {
            sum += nums[i];
            int rem = sum % k;
	    if (rem < 0) rem += k;
            if (rem == 0) count++;
            
            int max_mult = sum/k;
            for (int j=0; sum-max_mult*k - k*j>=max_neg; j++) {
                int check = sum - max_mult * k - j*k;
                count += rem_counts[check];
            }
            
            rem_counts[rem]++;
            if (sum < max_neg) {
                max_neg = sum;
            }
        }
        
        return count;
    }

};
