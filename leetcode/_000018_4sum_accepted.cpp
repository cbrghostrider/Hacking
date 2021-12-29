class Solution {
    string signature(const vector<int>& vec) {
        string ret = to_string(vec.size()) + ": ";
        for (int n : vec) {
            ret += to_string(n) + ";";
        }
        return ret;
    }
    
    string signature(int num1, int num2) {
        if (num1 > num2) {
            int temp=num1;
            num1=num2;
            num2=temp;
        }
        return (to_string(num1) + ":" + to_string(num2));
    }
    
    pair<int, int> components(const string& sig) {
        int pos = sig.find_first_of(":");
        int num1 = stoi(sig.substr(0, pos));
        int num2 = stoi(sig.substr(pos+1));
        return make_pair(num1, num2);
    }
    
public:    
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        unordered_map<long, unordered_set<string>> two_sums;
        unordered_map<int, int> counts;
        
        for (int n: nums) {counts[n]++;}
        
        for (int i=0; i<nums.size(); i++) {
            for (int j=i+1; j<nums.size(); j++) {
                long sum = nums[i] + nums[j];
                string sig = signature(nums[i], nums[j]);
                two_sums[sum].insert(sig);
            }
        }
        
        unordered_map<string, vector<int>> s;
        for (int i=0; i<nums.size(); i++) {
            for (int j=i+1; j<nums.size(); j++) {
                long sum = nums[i] + nums[j];
                long check = (long)target - sum;
                if (two_sums.find(check) == two_sums.end()) continue;
                
                for (const string& sig : two_sums[check]) {
                    pair<int, int> comps = components(sig);
                    
                    int check_count_a=0, check_count_b=0;
                    if (nums[i] == nums[j]) {
                        if (comps.first == comps.second && comps.second == nums[i]) {
                            check_count_a=3;
                            check_count_b=3;
                        } else if (comps.first == nums[i]) {
                            check_count_a=2;
                        } else if (comps.second == nums[i]) {
                            check_count_b=2;
                        }
                    } else if (comps.first == comps.second) {
                        if (nums[i] == comps.first || nums[j] == comps.first) {
                            check_count_a=2; check_count_b=2;
                        }                        
                    } else {
                        if (nums[i] == comps.first) {check_count_a++;}
                        if (nums[j] == comps.first) {check_count_a++;}
                        if (nums[i] == comps.second) {check_count_b++;}
                        if (nums[j] == comps.second) {check_count_b++;}
                    }
                    
                    if (counts[comps.first] <= check_count_a) continue;
                    if (counts[comps.second] <= check_count_b) continue;
                    
                    vector<int> ss = {nums[i], nums[j], comps.first, comps.second};
                    std::sort(ss.begin(), ss.end());
                    string sig2 = signature(ss);
                    s[sig2] = ss; 
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
