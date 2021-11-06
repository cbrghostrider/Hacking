class Solution {
public:
    // O(nlogn) time, O(n) space.
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        unordered_map<int, int> smaller_count;
        
        vector<int> ans = nums;
        std::sort(ans.begin(), ans.end());
        
        for (int i=0; i<ans.size(); ) {
            int ptr = i+1;
            while (ptr < ans.size() && ans[i] == ans[ptr]) ptr++;
            smaller_count[ans[i]] = i;
            i = ptr;
        }
        
        for (int i=0; i<nums.size(); i++) {
            nums[i] = smaller_count[nums[i]];
        }
        return nums;
    }
};
