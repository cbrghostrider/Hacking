class Solution {
    std::unordered_set<int> snums;
public:
    // using a set
    // O(n) space, O(n) time
    vector<int> findDisappearedNumbers2(vector<int>& nums) {
        for (int n : nums) {snums.insert(n);}
        vector<int> ans;
        for (int i = 0; i<nums.size(); i++) {
            if (snums.find(i+1) == snums.end()) {ans.push_back(i+1);}
        }
        return ans;
    }
    
    // using sort
    // O(1) space, O(nlogn) time
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        vector<int> ans;
        int last = 0;
        for (int i = 0; i<nums.size(); i++) {
            if (last + 1 < nums[i]) {
                for (int n = last+1; n < nums[i]; n++) {
                    ans.push_back(n);
                }
            }
            last = nums[i];
        }
        
        for (last++; last <= nums.size(); last++) {
            ans.push_back(last);
        }
        
        return ans;
    }
};
