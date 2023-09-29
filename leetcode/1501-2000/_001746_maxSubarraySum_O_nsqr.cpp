class Solution {
public:    
    // O(n^2) time, O(n^2) space.
    // For each sequence [i, j] we will keep a record of:
    // sum of those elements (inclusive), and,
    // the value of the element that has max abs value in that sequence
    // then go through all n^2 candidates and choose the optimal.
    int maxSumAfterOperation(vector<int>& nums) {
        vector<int> csum(nums.size(), 0);
        const int N = nums.size();
        int sum=0;
        for (int i=0; i<N; i++) {
            sum += nums[i];
            csum[i] = sum;
        }
        
        vector<vector<int>> chosen(N, vector<int>(N, 0));
        for (int i=0; i<N; i++) {
            for (int j=i; j<N; j++) {
                if (j == i) { chosen[i][j] = nums[j]; continue; }
                int choose=0;
                if (abs(chosen[i][j-1]) > abs(nums[j])) {
                    choose = chosen[i][j-1];
                } else if (abs(chosen[i][j-1]) < abs(nums[j])) {
                    choose = nums[j];
                } else {  // abs are equal, so choose the negative if you can
                    choose = (chosen[i][j-1] > nums[j] ? nums[j] : chosen[i][j-1]);
                }
                chosen[i][j] = choose;
            }
        }
        
        int max_subarray_sum = std::numeric_limits<int>::min();
        for (int i=0; i<N; i++) {
            for (int j=i; j<N; j++) {
                int subarray_sum = (i == j ? nums[j] : csum[j] - (i == 0 ? 0 : csum[i-1]));
                // let's maximize it now
                subarray_sum += chosen[i][j]*chosen[i][j] - chosen[i][j];
                if (subarray_sum > max_subarray_sum) {
                    max_subarray_sum = subarray_sum;
                }
            }
        }
        return max_subarray_sum;
    }
};
