// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// Takes O(n) time since each element is moved exactly once
// Takes O(1) space since movement is done in-place
class Solution {
public:
    void rotateFromIndForIter(vector<int>& nums, int k, int from, int forit) {
        int ctr=0, ind=from;
        int templast = nums[ind], tempnext;
        while (ctr < forit) {
            int nextind = (ind + k) % nums.size();
            tempnext = nums[nextind];
            nums[nextind] = templast;
            templast = tempnext;
            ind = nextind;
            ctr++; //one copy done
        }
    }
    int gcd(int a, int b) {
        int c = a % b;
        while(c != 0) {
            a = b;
            b = c;
            c = a % b;
        }
        return b;
    }
    int lcm (int a, int b) {
        return ((a < b) ? ((a*b)/gcd(b, a)) : ((a*b)/gcd(a, b)));
    }
    void rotateInPlace(vector<int>& nums, int k) {
        int lcmnk = lcm(nums.size(), k);
        if (gcd(nums.size(), k) == 1) {
            rotateFromIndForIter(nums, k, 0, nums.size());
        } else {
            int innerIter = lcmnk/k;
            int outerIter = nums.size()/innerIter;
            for (int i=0; i<outerIter; i++) {
                rotateFromIndForIter(nums, k, i, innerIter);
            }
        }
    }
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        if (k <= 0) return;
        rotateInPlace(nums, k);    
    }
};
