class Solution {
    string signature(const vector<int>& vec) {
        string ret = to_string(vec.size()) + ": ";
        for (int n : vec) {
            ret += to_string(n) + ";";
        }
        return ret;
    }
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        unordered_map<int, int> counts;
        for (int n: nums) {counts[n]++;}
        
        unordered_map<string, vector<int>> s;
        for (int i=0; i<nums.size(); i++) {
            for (int j=i+1; j<nums.size(); j++) {
                for (int k=j+1; k<nums.size(); k++) {
                    long ssum = (long)nums[i] + (long)nums[j] + (long)nums[k];
                    long check = (long)target - ssum;
                    int check_count=0;                    
                    if (nums[i] == check) {check_count++;}
                    if (nums[j] == check) {check_count++;}
                    if (nums[k] == check) {check_count++;}
                    if (counts.find(check) != counts.end() && 
                        counts[check] > check_count) {                                           
                        vector<int> ss = {nums[i], nums[j], nums[k], (int)check};
                        std::sort(ss.begin(), ss.end());
                        string sig = signature(ss);
                        s[sig] = ss;                        
                    }
                }
            }
        }
        
        vector<vector<int>> ans;
        for (const auto& kv : s) {
            ans.push_back(kv.second);
        }
        return ans;
    }
};
