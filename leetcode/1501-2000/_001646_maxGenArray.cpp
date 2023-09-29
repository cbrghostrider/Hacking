class Solution {
public:
    // O(n) time, O(n) space.
    int getMaximumGenerated(int n) {
        vector<int> gen(n+1, 0);
        gen[0] = 0; 
        if (n > 0) gen[1] = 1;
        for (int p=2; p<=n; p++) {
            if (p%2 == 0) {
                gen[p] = gen[p/2];
            } else {
                gen[p] = gen[p/2] + gen[p/2 + 1];
            }
        }
        int max = gen[0];
        for (int i=0; i<=n; i++) {
            if (gen[i] > max) max = gen[i];
        }
        return max;
    }
};
