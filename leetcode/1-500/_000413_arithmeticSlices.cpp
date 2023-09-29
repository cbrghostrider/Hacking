class Solution {
public:
    // O(n*n) time, O(n*n) space.
    // Can be optimized for O(n) space by only keeping the last row of is_arithmetic.
    // i.e. only needs prev and curr rows for is_arithmetic.
    int numberOfArithmeticSlices2(vector<int>& nums) {
        if (nums.size() <= 2) return 0;
        const int N = nums.size();
        int total=0;
        
        // indexed by (i, sz)
        // Answers the question: Is subarray starting at i, of size sz, an arithmetic subarray.
        vector<vector<bool>> is_arithmetic(N, vector<bool>(N+1, false));
        
        // Base case.
        for (int i=0; i<=N-3; i++) {
            if (nums[i] - nums[i+1] == nums[i+1] - nums[i+2]) {
                is_arithmetic[i][3] = true;
                total++;
            }
        }
        
        // DP.
        for (int sz=4; sz<=N; sz++) {
            for (int i=0; i<=N-sz; i++) {
                if (!is_arithmetic[i][sz-1]) continue;
                if (nums[i+sz-2] - nums[i+sz-1] == nums[i+sz-3] - nums[i+sz-2]) {
                    is_arithmetic[i][sz] = true;
                    total++;
                }
            }
        }
        return total;
    }
    
    // O(n) time, O(1) space.
    int numberOfArithmeticSlices(vector<int>& nums) {
        if (nums.size() <= 2) return 0;
        
        // Base case.
        int last_arithmetics = ((nums[0]-nums[1] == nums[1]-nums[2]) ? 1 : 0);
        int total = last_arithmetics;
        
        // DP.
        for (int i=3; i<nums.size(); i++) {
            if (last_arithmetics != 0) {
                if (nums[i-1] - nums[i] == nums[i-2] - nums[i-1]) {
                    last_arithmetics += 1;
                    total += last_arithmetics;
                } else {
                    last_arithmetics = 0;
                }
            } else {
                if (nums[i-1] - nums[i] == nums[i-2] - nums[i-1]) {
                    last_arithmetics = 1;
                    total += last_arithmetics;
                }
            }
        }
        return total;
    }
};
