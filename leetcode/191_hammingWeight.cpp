class Solution {
public:
    int hammingWeight(uint32_t n) {
        uint32_t mask = 0x1;
        int wt=0;
        while (mask) {
            wt = (mask & n) ? wt + 1 : wt;
            mask <<= 1;
        }
        return wt;
    }
};
