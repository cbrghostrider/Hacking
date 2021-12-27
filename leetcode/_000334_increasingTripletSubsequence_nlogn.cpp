class Solution {
    struct Info {
        int val=0;
        int index=0;
    };
public:
    // O(n log n) time, O(n) space.
    bool increasingTriplet(vector<int>& nums) {
        auto comp = [](const Info& lhs, const Info& rhs) -> bool {
            if (lhs.val != rhs.val) return lhs.val < rhs.val;
            return lhs.index > rhs.index;
        };
        priority_queue<Info, vector<Info>, decltype(comp)> max_heap(comp);
        priority_queue<int, vector<int>, std::greater<int>> min_heap;
        
        for (int i=0; i<nums.size(); i++) {max_heap.push({nums[i], i});}
        
        for (int i=0; i<nums.size(); i++) {
            while (!max_heap.empty() && max_heap.top().index <= i) {max_heap.pop();}
            bool lhs_conforms = !min_heap.empty() && min_heap.top() < nums[i];
            bool rhs_conforms = !max_heap.empty() && max_heap.top().val > nums[i];
            if (lhs_conforms && rhs_conforms) return true;
            min_heap.push(nums[i]);
        }
        return false;
    }
};
