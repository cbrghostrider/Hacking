class Solution {
    struct Info {
        int val=0;
        int index=0;
    };
public:
    // O(n log n) time, O(n) space.
    int longestSubarray(vector<int>& nums, int limit) {
        auto lcomp = [](const Info& lhs, const Info& rhs) -> bool {
            if (lhs.val != rhs.val) {return lhs.val > rhs.val;}
            return lhs.index > rhs.index;
        };
        auto gcomp = [](const Info& lhs, const Info& rhs) -> bool {
            if (lhs.val != rhs.val) {return lhs.val < rhs.val;}
            return lhs.index > rhs.index;
        };
        using MinHeap = priority_queue<Info, vector<Info>, decltype(lcomp)>;
        using MaxHeap = priority_queue<Info, vector<Info>, decltype(gcomp)>;
        
        MinHeap min_heap(lcomp);
        MaxHeap max_heap(gcomp);
        
        int s_ptr=0, e_ptr=0;
        int max_len=0;
        
        auto helper = [&s_ptr, &e_ptr, &nums, &max_len, &min_heap, &max_heap]() {
            min_heap.push({nums[e_ptr], e_ptr});
            max_heap.push({nums[e_ptr], e_ptr});
            e_ptr++;
            int len = e_ptr-s_ptr;
            max_len = std::max(len, max_len);
        };
        
        while (e_ptr < nums.size()) {
            while (!min_heap.empty() && min_heap.top().index < s_ptr) { min_heap.pop(); }
            while (!max_heap.empty() && max_heap.top().index < s_ptr) { max_heap.pop(); }    
            
            int new_val = nums[e_ptr];
            
            if (s_ptr == e_ptr) {
                helper();                
            } else if (std::abs(new_val-min_heap.top().val) <= limit && 
                       std::abs(new_val-max_heap.top().val) <= limit) {
                helper();
            } else {
                s_ptr++;
            }
        }
        
        return max_len;
    }
};
