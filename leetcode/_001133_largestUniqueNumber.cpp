class Solution {
public:
    // O(n) time, O(n) space.
    int largestUniqueNumber2(vector<int>& nums) {
        std::priority_queue<int, vector<int>, std::less<int>> max_heap;
        std::unordered_map<int, int> counts;
        for (int n : nums) {
            counts[n]++;
            max_heap.push(n);
        }
        while (!max_heap.empty()) {
            int n = max_heap.top();
            max_heap.pop();
            if (counts[n] == 1) return n;
        }
        return -1;
    }
    
    // O(nlogn) time, O(1) space.
    int largestUniqueNumber(vector<int>& nums) {
        std::sort(nums.begin(), nums.end(), std::greater<int>());
        for (int p1=0; p1<nums.size(); ) {
            int p2 = p1;
            while (p2 < nums.size() && nums[p1] == nums[p2]) { p2++; }
            if (p2-1 == p1) return nums[p1];
            p1 = p2;
        }
        return -1;
    }
};
