class Solution {
 public:
    // O(n) time, O(n) space.
    int findMaxLength(vector<int>& nums) {
        // we can +1 every time we encounter a 1, and -1 every time we encounter a 0
        // "earliest" records the earliest index where 0s and 1s "summed" to a certain value
        unordered_map<int, int> earliest;
        
        int total=0;
        int best=0;
        earliest[0] = -1;  // in case we match the whole array
        for (int i=0; i<nums.size(); i++) {
            total += (nums[i] == 0) ? -1 : 1;
            if (earliest.find(total) == earliest.end()) {
                earliest[total] = i;
            } else {
                int cand = i - earliest[total];
                best = std::max(best, cand);
            }
        }
        return best;
    }
};
