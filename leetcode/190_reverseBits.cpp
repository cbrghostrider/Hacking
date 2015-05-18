class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t mask=0x1, rmask = (0x1 << (((sizeof (uint32_t)) * 8) - 1));
        uint32_t result=0;
        while (mask) {
            if (mask & n) result |= rmask;
            mask <<= 1;
            rmask >>= 1;
        }
        return result;
    }
};
