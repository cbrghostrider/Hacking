// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int jump(vector<int>& nums) {
        
        //dynamic programming cache
        vector<int> numJumps(nums.size(), 0);
        
        //dynamic programming loop
        for (int i=nums.size()-2; i>=0; i--) {
            if (nums[i] <= 0) {
                numJumps[i] = -1; //not possible
                continue;
            }
            int minJumps = std::numeric_limits<int>::max();
            bool foundMin = false;
            for (int ind=i+1; ind<=i+nums[i] && ind < nums.size(); ind++) {
                if (numJumps[ind] == -1) continue;
                int theseJumps = 1 + numJumps[ind];
                if (theseJumps <= minJumps) {
                    minJumps = theseJumps;
                    foundMin = true;
                }
            }
            if (foundMin) {
                numJumps[i] = minJumps;
            } else {
                numJumps[i] = -1; //could not find any way to get to end from here
            }
        }
        
        return numJumps[0];
    }
};
