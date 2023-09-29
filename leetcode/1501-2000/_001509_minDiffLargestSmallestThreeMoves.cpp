class Solution {
    
    // The reason we need the middle 2 is because if we end up dropping the first 3 (or last 3)
    // then the middle number becomes significant in computing the lowest diff
    //
    // operates on no more than 8 (3 smallest, 2 middle, 3 largest) from the original array
    // may operate on less than that
    // strikes says how many changes are remaining
    //
    // The cool thing is that even with the brute force recursion, this recursive call
    // takes only O(1) time. 
    // That's because nums is no more than 8, strikes no more than 3.
    // So the amount of recursion (i.e. total work) is fixed at some small value.
    int minDiff6(vector<int> nums, int strikes) {
        if (nums.size() == 0) return 0;
        if (strikes == 0 || nums.size() == 1) {
            return (nums.back() - nums[0]);
        }
        vector<int> nums2;
        nums2.insert(nums2.end(), nums.begin()+1, nums.end());
        int md1 = minDiff6(nums2, strikes-1);
        
        nums.pop_back();
        int md2 = minDiff6(nums, strikes-1);
        return std::min(md1, md2);
    }
    
public:
    
    // O(n) time, O(1) space.
    int minDifference(vector<int>& nums) {
        if (nums.size() <= 8) {
            std::sort(nums.begin(), nums.end());
            return minDiff6(nums, 3);
        }
        
        // heaps take only O(1) space, as they carry no more than 4 at a time.
        // for the same reason, operations on the heap only take O(1) time.
        priority_queue<int, vector<int>, std::less<int>>    max_heap;  // stores smallest 4 nums
        priority_queue<int, vector<int>, std::greater<int>> min_heap;  // stores largest 4 nums
        for (int n : nums) {
            max_heap.push(n); if (max_heap.size() > 4) { max_heap.pop(); }
            min_heap.push(n); if (min_heap.size() > 4) { min_heap.pop(); }
        }
        
        vector<int> nums2;
        while (!max_heap.empty()) {nums2.push_back(max_heap.top()); max_heap.pop();}
        std::reverse(nums2.begin(), nums2.end());
        while (!min_heap.empty()) {nums2.push_back(min_heap.top()); min_heap.pop();}
        return minDiff6(nums2, 3);
    }
};
