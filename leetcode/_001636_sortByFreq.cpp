class Solution {
public:
    // O(nlogn) time, O(n) space.
    vector<int> frequencySort(vector<int>& nums) {
        unordered_map<int, int> freqs;
        for (int n: nums) freqs[n]++;
        std::sort(nums.begin(), nums.end(), [&freqs](int left, int right) -> bool {
            if (freqs[left] != freqs[right]) {
                return freqs[left] < freqs[right];
            }
            return left > right;
        });
        return nums;
    }
};
