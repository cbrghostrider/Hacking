class Solution {

    // returns the "index" of x
    int binSearch(const vector<int>& arr, int x, int lo, int hi) {
        if (lo == hi) return lo;
        if (lo+1 == hi) {
            if (arr[hi] == x) return hi;
            return lo;
        }
        int mid=(lo+hi)/2;
        if (arr[mid] == x) return mid;
        if (arr[mid] > x) return binSearch(arr, x, lo, mid);
        return binSearch(arr, x, mid+1, hi);
    }
    
public:
    // O(k log k + log n) time, O(k + log n) space (including recursion stack space).
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int index = binSearch(arr, x, 0, arr.size()-1);
        
        auto comp = [x](const int& lhs, const int& rhs) -> bool {
            int adiff_l = std::abs(lhs-x);
            int adiff_r = std::abs(rhs-x);
            if (adiff_l != adiff_r) return adiff_l < adiff_r;
            return lhs < rhs;
        };
        priority_queue<int, vector<int>, decltype(comp)> max_heap(comp);
        
        int ind_lo = index-k < 0 ? 0 : index-k;
        int ind_hi = index+k >= arr.size() ? arr.size()-1 : index+k;
        
        for (int i=ind_lo; i<=ind_hi; i++) {
            max_heap.push(arr[i]);
            if (max_heap.size() > k) { max_heap.pop(); }
        }
        
        vector<int> ans;
        while (!max_heap.empty()) {
            int elem = max_heap.top();
            max_heap.pop();
            ans.push_back(elem);
        }
        std::sort(ans.begin(), ans.end());
        return ans;
    }
};
