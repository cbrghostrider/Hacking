class Solution {
public:
    // O(nlogn) time due to sort.
    // O(n) space for k=0, O(1) space for other k.
    int findPairs(vector<int>& nums, int k) {
        if (nums.size() <= 1) return 0;
        if (k == 0) {
            std::unordered_map<int, int> counts;
            for (int n : nums) {counts[n]++;}
            int repeats=0;
            for (const auto& kv : counts) {
                if (kv.second > 1) {repeats++;}
            }
            return repeats;
        }
        
        std::sort(nums.begin(), nums.end());
        const int orig_size = nums.size();
        int s_ptr=0;  // last valid number we want to keep
        int l_ptr=0;  // number we want to swap (eventually)
        while (l_ptr < nums.size()) {
            while (l_ptr < nums.size() && nums[s_ptr] == nums[l_ptr]) {l_ptr++;}
            if (l_ptr == nums.size()) break;
            std::swap(nums[++s_ptr], nums[l_ptr++]);
        }
        s_ptr++;  // one beyond the last number we keep
        nums.erase(std::begin(nums) + s_ptr, nums.end());
        
        int nk_diffs=0;
        for (int i=0, j=1; i<nums.size() && j<nums.size(); ) {
            while (j<nums.size() && std::abs(nums[i] - nums[j]) < k) {j++;}
            if (j == nums.size()) {break;}
            if (nums[j] - nums[i] == k) {
                nk_diffs++; i++; j++;
            }
            if (j == nums.size()) {break;}
            while (i<nums.size() && i<=j && std::abs(nums[i]-nums[j]) > k) {i++;}
        }
        return nk_diffs;
    }
};
