class Solution {
public:
    // O(n log n) time, O(n) space.
    // Greedy algorithm.
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        vector<pair<int, int>> n2_inds;
        for (int i=0; i<nums2.size(); i++) {
            n2_inds.push_back({nums2[i], i});
        }
        std::sort(n2_inds.begin(), n2_inds.end(), 
                  [](const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
            if (lhs.first != rhs.first) return lhs.first > rhs.first;
            return lhs.second > rhs.second;
        });
        
        priority_queue<int, vector<int>, std::greater<int>> min_heap;
        for (int n : nums1) {min_heap.push(n);}
        
        vector<int> ans(nums1.size(), -1);
        vector<int> rejects;
        for (int i=n2_inds.size()-1; i>=0 && !min_heap.empty(); ) {
            if (n2_inds[i].first < min_heap.top()) {
                ans[n2_inds[i].second] = min_heap.top();
                i--;
            } else {
                rejects.push_back(min_heap.top());
            }
            min_heap.pop();
        }
        for (int i=0, r=0; i<ans.size(); i++) {
            if (ans[i] == -1) {
                ans[i] = rejects[r++];
            }
        }
        return ans;
    }
};
