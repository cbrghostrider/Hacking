class Solution {
    struct Info {
        int max_first=std::numeric_limits<int>::min();
        int max_second=std::numeric_limits<int>::min();
        int max_sum=std::numeric_limits<int>::min();
    };
public:
    // For each index i, we will store the following.
    // 1. The sum of the max subarray of length firstLen so far.
    // 2. The sum of the max subarray of length secondLen so far.
    // (Note that 1 and 2 could overlap in this, we will handle that in the recurrence).
    // 3. The max sum of 2 non-overlapping subarrays of firstLen and secondLen.
    // Let us call this struct Info.
    // 
    // When a new index i is added to existing i-1 elements, we have 3 cases:
    // 1. The max sum remains unchanged, because the added element in inconsequential.
    // 2. The max sum changes, because the added index forms a new firstLen sized subarray ending at i.
    // 3. The max sum changes, because the added index forms a new secondLen sized subarray ending at i.
    // We choose the max of these 3 choices.
    //
    // O(n) time, O(n) space.
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        if (firstLen + secondLen > nums.size()) return 0;
        // make it so firstlen always smaller than secondlen
        if (firstLen > secondLen) {std::swap(firstLen, secondLen);}
        
        vector<Info> cache(nums.size(), Info());
                
        // Base cases.
        int first_sum=0, second_sum=0;          // stores first and second len sums.
        int max_first_sum=0, max_second_sum=0;  // stores maxes so far for the same
        for (int i=0; i<(firstLen+secondLen)-1; i++) {
            first_sum += nums[i];
            first_sum -= (i < firstLen ? 0 : nums[i-firstLen]);
            if (i >= firstLen-1) {
                if (first_sum > max_first_sum) { max_first_sum = first_sum;}
                cache[i].max_first = max_first_sum;
            }
            
            second_sum += nums[i];
            second_sum -= (i < secondLen ? 0 : nums[i-secondLen]);
            if (i >= secondLen-1) {
                if (second_sum > max_second_sum) { max_second_sum = second_sum;}
                cache[i].max_second = max_second_sum;
            }
        }
        
        // DP.
        // first_sum and second_sum carry over.
        for (int i=firstLen+secondLen-1; i<nums.size(); i++) {
            first_sum  += nums[i] - nums[i-firstLen];
            if (first_sum > max_first_sum) { max_first_sum = first_sum; }
            
            second_sum += nums[i] - nums[i-secondLen];
            if (second_sum > max_second_sum) { max_second_sum = second_sum; }
                        
            // 1. When the max sum remains unchanged.
            int c1 = cache[i-1].max_sum;
            
            // 2. When the current firstLen seq ending at i forms part of the solution.
            int first_seq_starts = i-firstLen+1;
            int c2 = cache[first_seq_starts-1].max_second + first_sum;
            
            // 3. When the current secondLen seq ending at i forms part of the solution.
            int second_seq_starts = i-secondLen+1;
            int c3 = cache[second_seq_starts-1].max_first + second_sum;       
            
            // Update cache;
            cache[i].max_first = max_first_sum;
            cache[i].max_second = max_second_sum;
            cache[i].max_sum = std::max(c1, std::max(c2, c3));
        }
        
        return cache[nums.size()-1].max_sum;
    }
};
