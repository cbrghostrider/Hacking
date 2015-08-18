// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(n^2) solution. Here is my writeup from leetcode:
//
// Although it has 3 loops, the innermost while loop does not reset its loop variable everytime. Here is my logic:
//
// I keep 3 pointers n1p, n2p, n3p.
//
// n2p is the pointer for the middle number, and increments by 1 in outermost loop.
//
// For each n2p, I fix a n1p such that n1p < n2p. This increments in the inner loop. Already we have reached O(n^2).
//
// Now comes the important part. For the very first n1p iteration (n1p==0), I start n3p from the rightmost position. 
// I move it left until the desired condition w/ target is hit. However, n3p does not reset in the while loop for 
// future iterations of n1p. So as n1p keeps moving right every inner iteration, n3p moves a few positions to the left as well. 
// Since n1p and n2p are fixed, the number of combos for this pair of (n1p, n2p) is the difference between n2p and n3p.
//
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int combos = 0;
        std::sort(nums.begin(), nums.end());
        for (int n2p=0; n2p<nums.size(); n2p++) {       //this is the middle number
            int n3p = nums.size()-1;                    //Don't reset this in inner loop! Important.
            for (int n1p=0; n1p < n2p && n2p < n3p; n1p++) {//this is the first number
                while(n3p>n2p && ((nums[n1p] + nums[n2p]) >= (target - nums[n3p]))) {
                    n3p--;
                }
                combos += (n3p - n2p);
            }
        }
        return combos;
    }
};
