class Solution {
public:
    // O(n) runtime, O(1) space.
    int concatenatedBinary(int n) {
        int ans=0;
        
        for (int i=1; i<=n; i++) {
            uint32_t loc = (1 << 31);
            while ((i & loc) == 0) {loc >>= 1;}
            while (loc) {
                ans *= 2;
                if (i & loc) {ans += 1;}
                ans %= 1000000007;
                loc >>= 1;
            }
        }
        return ans;
    }
};
