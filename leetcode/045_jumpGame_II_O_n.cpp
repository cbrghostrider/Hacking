// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
public:
    int jump(vector<int>& nums) {
        int steps=0;                     //current steps count
        int far=0;                       //this is as far as I can go with "steps" steps
        int nextfar=0;                   //this is as far as I can go with "steps+1" steps
        
        for (int ind=0; ind<nums.size() && far<nums.size()-1; ind++) {
            int check = ind + nums[ind]; //this is as far as I can go from here
            if (ind == far) {            //update steps, and update far to nextfar
                steps++;
                far = (check > nextfar) ? check : nextfar;
                nextfar = far;
            } else if (check > nextfar) {//update furthest I can go in steps+1
                nextfar = check;
            }
        }
        return steps;
    }
};
