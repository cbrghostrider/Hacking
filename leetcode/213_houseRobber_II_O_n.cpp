// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    //if force0Rob is true,  I HAVE to     rob 0-th house
    //if force0Rob is false, I HAVE to NOT rob 0th house
    int robPrime(vector<int>& nums, bool force0Rob) {
        
        //dynamic programming cache; money made by robbing *optimal choices* of houses until index i
        vector<int> money(nums.size(), 0);
        money[0] = force0Rob ? nums[0] : 0;
        money[1] = force0Rob ? nums[0] : nums[1];
        
        //dynamic programming loop
        for (int i=2; i<nums.size()-1; i++) {
            int cand1 = nums[i] + money[i-2];
            int cand2 = money[i-1];
            money[i] = cand1 > cand2 ? cand1 : cand2;
        }
        
        //last place
        int last = nums.size() - 1;
        int lastbutone = nums.size() - 2;
        int lastbuttwo = nums.size() - 3;
        money[last] = force0Rob ? (max(money[lastbutone], money[lastbuttwo])) 
                                : (max(money[lastbutone], money[lastbuttwo] + nums[last]));
        return money[last];
    }
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return max(nums[0], nums[1]);
        return (max(robPrime(nums, true), robPrime(nums, false)));
    }
};
