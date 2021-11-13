class Solution {
    // between [left, right] inclusive.
    // O(nlogn) time, O(1) space.
    void maxDiffDivAndConq(const vector<int>& nums, int left, int right,
                          int& max_diff, int& min, int& max) {
        if (right - left <= 2) {
            min = std::numeric_limits<int>::max();
            max = std::numeric_limits<int>::min();
            for (int i=left; i<=right; i++) {
                if (nums[i] <= min) min = nums[i];
                if (nums[i] >= max) max = nums[i];
            }
            max_diff = -1;
            for (int i=left; i<=right; i++) {
                for (int j=i+1; j<=right; j++) {
                    int diff = nums[j] - nums[i];
                    if (nums[i] < nums[j] && diff > max_diff) {
                        max_diff = diff;
                    }
                }
            }
            return;
        }
        
        int mid = (right + left)/2;
        int min_l, min_r, max_l, max_r, max_diff_l, max_diff_r;
        min_l = min_r = std::numeric_limits<int>::max();
        max_l = max_r = std::numeric_limits<int>::min();
        max_diff_l = max_diff_r = -1;
        maxDiffDivAndConq(nums, left, mid, max_diff_l, min_l, max_l);
        maxDiffDivAndConq(nums, mid+1, right, max_diff_r, min_r, max_r);
        int max_diff_cross = (min_l < max_r ? max_r - min_l : -1);
        
        max_diff = std::max(max_diff_cross, std::max(max_diff_l, max_diff_r));
        min = std::min(min_l, min_r);
        max = std::max(max_l, max_r);
    }
    
public:
    int maximumDifference(vector<int>& nums) {
        int md=-1, min=-1, max=-1;
        maxDiffDivAndConq(nums, 0, nums.size()-1, md, min, max);
        return md;
    }
};
