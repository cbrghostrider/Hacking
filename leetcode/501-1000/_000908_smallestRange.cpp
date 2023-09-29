class Solution {
public:
    // O(n) time, O(1) space.
    int smallestRangeI(vector<int>& nums, int k) {
        int largest = std::numeric_limits<int>::min();
        int smallest = std::numeric_limits<int>::max();
        for (int n : nums) {
            if (n > largest) largest = n;
            if (n < smallest) smallest = n;
        }
        int diff = largest-smallest;
        return (diff > 2*k ? diff - 2*k : 0);
    }
};
