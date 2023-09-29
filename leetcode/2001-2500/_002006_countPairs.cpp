class Solution {
public:
    // O(n) time, O(n) space.
    int countKDifference(vector<int>& nums, int k) {
        int pairs = 0;
        std::unordered_map<int, int> counts;
        for (int n : nums) {
            pairs += counts[n-k];
            pairs += counts[n+k];
            counts[n]++;
        }
        return pairs;
    }
};
