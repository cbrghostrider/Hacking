class Solution {
public:
    // Simple loop solution.
    vector<int> countBits(int n) {
        vector<int> ans;
        for (uint32_t i=0; i<=n; i++) {
            uint32_t mask = 0x1;
            int count = 0;
            for (int p=0; p<32; p++) {
                if (i & mask) count++;
                mask <<= 1;
            }
            ans.push_back(count);
        }
        return ans;
    }
};
