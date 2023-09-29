class Solution {
    struct Info {
        int val=0;
        int index=0;
    };
    
    function<bool(const Info&, const Info&)> comp = [](const Info& lhs, const Info& rhs) -> bool {
        if (lhs.val != rhs.val) return lhs.val < rhs.val;
        return lhs.index > rhs.index;
    };
    
    using MaxHeap=priority_queue<Info, vector<Info>, decltype(comp)>;
    
public:
    // O(n log n) time, O(n) space.
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {        
        MaxHeap heap(comp);
        
        // Initialize
        int i=0;
        for (; i<k && i<nums.size(); i++) {
            heap.push({nums[i], i});
        }
        
        vector<int> best;
        best.push_back(heap.top().val);
        
        for (; i<nums.size(); i++) {
            while (!heap.empty() && heap.top().index <= i-k) {
                heap.pop();
            }
            heap.push({nums[i], i});
            best.push_back(heap.top().val);
        }
        
        return best;
    }
};
