class Solution {
public:
    // the powerset is a set of subsets; each subset may or may not contain an element from nums
    // the presence or absence of each element, and thus each set itself, can be represented as a binary number
    // so PowSet({x, y, z}) can be represented by all binary numbers from 000 to 111
    // where if the bit is set, that number is included in that specific subset
    // O(n*2^n) time, O(1) space.
    int subsetXORSum(vector<int>& nums) {
        const int N = nums.size();
        const int pnums = (int)(pow(2.0, (double)N));
        int xsum = 0;
        for (int n=0; n<pnums; n++) {
            unsigned int mask = 0x1;
            int xval = 0;
            for (int i=0; i<N; i++) {
                if (n & mask) {xval ^= nums[i];}
                mask <<= 1;
            }
            xsum += xval;
        }
        return xsum;
    }
};
