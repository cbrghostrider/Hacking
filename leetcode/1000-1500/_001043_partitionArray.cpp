class Solution {
public:
    // Consider the starting chunk. 
    // This chunk can range in size from 1 to k.
    // To find the optimal choice, we will try all values (using DP), and pick the best.
    // 
    // Recurrence, for chunk starting at index i:
    // maxSum(i) = try all values from 1 to k -> let this number be n, 
    //    for each choice: maxVal[i... i+n-1] + maxSum(i+n)
    //    choose the value of n that gives max across all choices
    //
    // O(n*k) time, O(n) space.
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        vector<int> maxSum(arr.size(), 0);
        
        // Base case.
        int max = std::numeric_limits<int>::min();
        for (int i=arr.size()-1, sz=1; i>=((int)arr.size())-k; i--, sz++) {
            if (arr[i] > max) {max = arr[i];}
            maxSum[i] = max * sz;
        }
        
        // DP cases.
        for (int i=arr.size()-k-1; i>=0; i--) {
            int max = std::numeric_limits<int>::min();
            int my_chunk_max = std::numeric_limits<int>::min();
            for (int ci=i, sz=1; ci<i+k; ci++, sz++) {
                if (arr[ci] > my_chunk_max) {my_chunk_max = arr[ci];}
                int my_sum = my_chunk_max*sz + maxSum[ci+1];
                if (my_sum > max) {max = my_sum;}
            }
            maxSum[i] = max;
        }
        
        return maxSum[0];
    }
};
