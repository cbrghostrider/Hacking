class Solution {
    
    set<vector<int>> takeItDropIt(const set<vector<int>>& ss, int val) {
        set<vector<int>> ss1 = ss;
        vector<vector<int>>ss2;
        ss2.insert(ss2.end(), ss.begin(), ss.end());
        for (vector<int>& s : ss2) {
            if (s.size() >= 1 && val < s.back()) continue;  // prune search space earlier!
            s.push_back(val);
            ss1.insert(s);
        }
        return ss1;
    }
    
public:
    // O(n!) time, brute force.
    // This version does early pruning as per the < property.
    // So we don't need to check for valid-ness later.
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        set<vector<int>> ss = {{}};
        
        for (int i=0; i<nums.size(); i++) {
            ss = takeItDropIt(ss, nums[i]);
        }
        vector<vector<int>> ans;
        
        for (const vector<int>& s : ss) {
            if (s.size() >= 2) {
                ans.push_back(s);
            }
        }
        return ans;
    }
};
