class Solution {
    
    // answer is modulo 1000000007
    long NchooseK(int n, int k) {
        if (k == 0 || k == n)  return 1;
        if (k == 1) return n;
                
        k = std::min(k, n-k);
        
        double ans=1;
        for (int i=0; i<k; i++) {
            ans *= (n-i);
            ans /= (i+1);
        }              
        
        return ans;
    }

    // [start, end] are indices of the numbers chosen
    // we update total, by considering all subsequences that can be built
    // using start index, and 0 or more numbers from start+1 to end (inclusive)
    // total is updated modulo 1000000007
    void updateTotal(long& total, int start, int end) {
        int N=end-start;  // from [start+1 ---> end]
        for (int k=1; k<=N; k++) {
            total += NchooseK(N, k);
            total %= 1000000007;
        }
    }
public:
    // 
    // This solution has a small bug somewhere...
    //
    // For smaller inputs, it functions fine. For larger inputs, it *very slowly*
    // diverges from the expected answer.
    //
    // My guess is that the modulo 1000000007 bullshit that needs to be done
    // to keep the numbers in line, is faulty w.r.t. n choose k.
    // 
    // I had to dip into double to keep it within limits, and after performing the
    // division, I simply return that value as a long.
    // My gut feeling tells me that this is broken when n choose k leads to huge values.
    //
    // Or I might be wrong, and the main loop below has some subtle bug...
    //
    // Here is an example test case that goes wrong:
    // [1, 2, 2, 2, 2, 2, 2, 6, 6, 7, 8, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 12, 12, 13, 
    //  14, 14, 14, 14, 15, 15, 15,17, 18, 18, 19, 19, 19, 19, 20, 20, 20, 21, 21, 21, 21, 
    //  22, 22, 22, 23, 24, 24, 26, 27, 27,28]
    //
    //  target = 31
    //  
    //  Expected: 442670495
    //  Actual: 442670491
    //
    //  The divergence is only 4 here, but as we increase the sequence size, the divergence 
    //  gradually increases. This is why I think it is a modulo arithmetic issue, because as 
    //  the numbers get larger, more of that comes into play. If it were a corner case in the 
    //  main loop, I would think that the bug happens once, and then probably not. So the 
    //  divergence of 4 would have remained constantly most likely...
    //
    //  Interestingly, if you delete the 28 at the end, it gets the right result....
    //
    int numSubseq(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        
        long total=0;        
        int s_ptr=0, e_ptr=0;
        
        while (s_ptr < nums.size() && s_ptr <= e_ptr) {                 
            while (e_ptr < nums.size() && nums[s_ptr] + nums[e_ptr] <= target) {                
                e_ptr++;
            }
            if (e_ptr-1 < s_ptr) {e_ptr = s_ptr+1;}
            int lowest=nums[s_ptr];
            int highest=nums[e_ptr-1];
            
            if (lowest * 2 <= target) {total += 1;}  // [n] is a valid subsequence
            // count number of subsequences with lowest in them.
            if (lowest+highest<=target) {                
                updateTotal(total, s_ptr, e_ptr-1);
            }
            s_ptr++;
            while (e_ptr > s_ptr && nums[s_ptr] + nums[e_ptr-1] > target) {
                e_ptr--;
            }
        }
        
        return total;
    }
};
