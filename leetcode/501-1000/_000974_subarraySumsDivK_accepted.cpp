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
    
    // O(n) time, O(n) space.
    int subarraysDivByK(vector<int>& nums, int k) {
        vector<int> csum(nums.size(), 0);
        
        // (val, count)
        // how many prior indices rem up to val.
        unordered_map<int, int> rem_counts;
        rem_counts[0] = 1;  // this is to account for csum before index 0
        
        int sum=0, count=0;
        for (int i=0; i<nums.size(); i++) {
            sum += nums[i];
            int rem = sum % k;
            
            // Jesus Christ... this took way too long.
            //
            // Basically think of 2 chunks of cumulative_rems
            // p1 = rem for 1st chunk
            // p2 = rem for 2nd chunk
            // 1st chunk is from [0...x]
            // 2nd chunk is from [0...y] ; x < y
            //
            // p2 - p1 = 0  ; in this case, the chunk sums up to 0
            // p2 - p1 = k  ; the chunk sums up to k
            // p2 - p1 = -k ; the chunk sums up to -k
            // all 3 of these chunk differences are counted
            //
            count += rem_counts[rem];
            count += rem_counts[-1*(k-rem)];
            count += rem_counts[(k+rem)];
            
            rem_counts[rem]++;
        }
        
        return count;
    }

};
