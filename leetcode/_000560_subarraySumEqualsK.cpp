class Solution {
public:
    // O(n) time, O(n) space.
    int subarraySum(vector<int>& nums, int k) {
        // counts how many indices sum up to key so far
        unordered_map<int, int> csum_counts;
        csum_counts[0] = 1;  // the null set sums up to 0 (i.e. index -1)
        
        // as you accumulate csum x at any step, count how many subarrays are valid
        // by looking back at which ones give (x-k)
        int sum=0, total=0;
        for (int n : nums) {
            sum += n;
            total += csum_counts[sum-k];
            csum_counts[sum]++;
        }
        return total;
    }
};
