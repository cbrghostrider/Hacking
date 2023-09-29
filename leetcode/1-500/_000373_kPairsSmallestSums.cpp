class Solution {
    struct Info {
        int u=0;
        int v=0;
    };
    function<bool(const Info&, const Info&)> comp = [this] (const Info& lhs, const Info& rhs) -> bool {
        return ((lhs.u+lhs.v) > (rhs.u+rhs.v));
    };
    using MinHeap = priority_queue<Info, vector<Info>, decltype(comp)>;
    MinHeap min_heap;
    
    int ptr1=0, ptr2=0;
    
    void addToHeap(const vector<int>& nums1, const vector<int>& nums2, bool advance_seq_1 = true) {
        // whether the addition is even possible
        bool validate = advance_seq_1 ? ptr1 < nums1.size()-1 : ptr2 < nums2.size()-1;
        if (!validate) return;
        
        int& ptr = advance_seq_1 ? ptr1 : ptr2;
        int& ptr_other = advance_seq_1 ? ptr2 : ptr1;
        
        ptr++;
        
        const vector<int>& nums = advance_seq_1 ? nums2 : nums1;
        int val = advance_seq_1 ? nums1[ptr] : nums2[ptr];
        
        for (int i=0; i<=ptr_other; i++) {
            Info info;
            if (advance_seq_1) {
                info = {val, nums[i]};
            } else {
                info = {nums[i], val};
            }
            min_heap.push(info);
        }
    }    
    
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {        
        vector<vector<int>> ans;
        if (nums1.size() == 1) {
            for (int i=0; i<nums2.size() && i < k; i++) {
                ans.push_back({nums1[0], nums2[i]});
            }
            return ans;
        }
        if (nums2.size() == 1) {
            for (int i=0; i<nums1.size() && i < k; i++) {
                ans.push_back({nums1[i], nums2[0]});
            }
            return ans;
        }
        
        if (nums1.size() * nums2.size() < k) {
            k = nums1.size() * nums2.size();
        }

        ans = {{nums1[0], nums2[0]}};
        k -= 1;
        
        min_heap = MinHeap(comp);
        auto& mmh = min_heap;
        addToHeap(nums1, nums2, true);
        addToHeap(nums1, nums2, false);
        
        while (k > 0) {
            // {ptr1+1, 0}
            int c1 = ptr1 == nums1.size()-1 ? std::numeric_limits<int>::max() : nums1[ptr1+1] + nums2[0];
            // {0, ptr2+1}
            int c2 = ptr2 == nums2.size()-1 ? std::numeric_limits<int>::max() : nums2[ptr2+1] + nums1[0];
            
            Info ch = min_heap.empty() ? Info({-1, -1}) : min_heap.top();
            int ch_val = min_heap.empty() ? std::numeric_limits<int>::max() : ch.u + ch.v;
            
            int best = std::min(ch_val, std::min(c1, c2));
            
            if (ch_val == best) {
                ans.push_back({ch.u, ch.v});
                min_heap.pop();
                k--;
            } else if (best == c1) {
                addToHeap(nums1, nums2, true);
            } else {
                addToHeap(nums1, nums2, false);
            }
        }
        return ans;
    }
};
