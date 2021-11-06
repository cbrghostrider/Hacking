class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> ans(n, 0);
        int m = n/2;
        int seed = 1;
        for (int mi=0; mi<m; mi++) {
            ans[2 * mi] = seed;
            ans[2 * mi + 1] = -1 * seed;
            seed++;
        }
        
        if (n % 2 != 0) {
            // 0 already present
        }
        return ans;
    }
};
