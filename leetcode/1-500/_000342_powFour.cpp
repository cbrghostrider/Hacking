class Solution {
public:
    bool isPowerOfFour2(int n) {
        if (n == 1) return true;
        if (n < 3) return false;
        long nl = (long)n, test=4;
        while (test <= nl) {
            if (test == nl) return true;
            test *= 4;
        }
        return false;
    }
    
    // Not using recursion, just counting bits.
    bool isPowerOfFour3(int n) {
        if (n == 1) return true;
        if (n < 3) return false;
        
        unsigned int np = n, count_tz=0;
        while((np & 0x1) == 0 && np != 0) {
            count_tz++;
            np >>= 1;
        }
        
        unsigned int npp=n, count_ones=0, mask=0x1;
        for (int i=0; i<32; i++) {
            if (npp & mask) {count_ones++;}
            mask <<= 1;
        }
        
        return (count_ones == 1 && (count_tz % 2) == 0);
    }

    // using caching
    bool isPowerOfFour(int n) {
        unordered_set<int> powers = {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 
                                     1048576, 4194304, 16777216, 67108864, 268435456, 
                                    1073741824};
        if (n < 1) return false;
        if (powers.find(n) == powers.end()) return false;
        return true;
    }
};
