class Solution {
    
    int getMaxLen(const vector<int>& small, const vector<int>& large) {
        int max_len=0;
        int sz=1;
        for (int end_l = 0; end_l < large.size(); end_l++) {
            int my_max=0;
            int ctr=0;
            for (int s=(int)small.size()-1, d=0; s >= (int)small.size()-sz; s--, d++) {
                int index_large = end_l - d;
                if (large[index_large] == small[s]) {
                    ctr++;
                } else {
                    my_max = std::max(my_max, ctr);
                    ctr=0;
                }
            }
            my_max = std::max(my_max, ctr);
            max_len = std::max(max_len, my_max);
            if (sz < small.size()) {sz++;}
        }
        return max_len;
    }
    
public:
    // O(n^2) time, O(1) space.
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        vector<int>& small = nums1.size() <= nums2.size() ? nums1 : nums2;
        vector<int>& large = nums1.size() <= nums2.size() ? nums2 : nums1;
        
        int l1 = getMaxLen(small, large);
        std::reverse(small.begin(), small.end());
        std::reverse(large.begin(), large.end());
        int l2 = getMaxLen(small, large);
        return std::max(l1, l2);
    }
};
