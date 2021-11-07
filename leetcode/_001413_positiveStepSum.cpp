class Solution {
public:
    // O(n) time, O(1) space.
    int minStartValue(vector<int>& nums) {
        int max_neg = std::numeric_limits<int>::max();
        int sum = 0;
        for (int n : nums) {
            sum += n;
            if (sum < max_neg) { max_neg = sum; }
        }
        return (max_neg >= 0 ? 1 : std::abs(max_neg) + 1);
    }
};
