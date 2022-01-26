class Solution {
    // lo/hi are indices
    // val is the val to check
    // returns {val', val''} > or < or == val, that are closest to val    
    pair<int, int> getClosest(const vector<int>& nums, int val, int lo, int hi) {
        if (lo == hi) {return {nums[lo], nums[lo]};}
        if (lo+1 == hi) { return {nums[lo], nums[hi]}; }
        
        int mid = (lo+hi)/2;
        if (nums[mid] == val) return {nums[mid], nums[mid]};
        if (nums[mid-1] <= val && val <= nums[mid]) return {nums[mid-1], nums[mid]};
        if (nums[mid] <= val && val <= nums[mid+1]) return {nums[mid], nums[mid+1]};
        
        if (val > nums[mid]) {
            return getClosest(nums, val, mid, hi);
        }
        return getClosest(nums, val, lo, mid);
    }
    
public:
    // O(n log n) time, O(n) space.
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {                        
        long sad = 0;
        for (int i=0; i<nums1.size(); i++) {
            long absdiff = std::abs(nums1[i] - nums2[i]);
            sad += absdiff;  
        }
        
        vector<int> nums_copy = nums1;
        std::sort(nums_copy.begin(), nums_copy.end());        
        
        long cand = sad;
        for (int index=0; index<nums1.size(); index++) {
            long absdiff = std::abs(nums1[index] - nums2[index]);
            int check = nums2[index];            
            
            auto choices = getClosest(nums_copy, check, 0, nums_copy.size()-1);
            int ad1 = std::abs(choices.first  - check);
            int ad2 = std::abs(choices.second - check);
            cand = std::min(cand, sad-absdiff + std::min(ad1, ad2));
        }
        return cand % 1000000007;
    }        
};
