class Solution {
    
    string vecSignature(const vector<int>& v) {
        string sig;
        for (int n : v) {sig += to_string(n) + "-";}
        return sig;
    }
    
    vector<vector<int>> ss;
    
    void takeItDropIt(int val) {
        vector<vector<int>> ss2 = ss;
        for (vector<int>& s : ss2) {
            s.push_back(val);
            ss.push_back(s);
        }
    }
    
    bool valid(const vector<int>& v) {
        if (v.size() < 2) return false;
        for (int i=1; i<v.size(); i++) {
            if (v[i] < v[i-1]) return false;
        }
        return true;
    }
    
public:
    // O(n!) time, brute force.
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        ss = {{}};
        
        for (int i=0; i<nums.size(); i++) {
            takeItDropIt(nums[i]);
        }
        unordered_set<string> sigs;
        vector<vector<int>> ans;
        for (const vector<int>& s : ss) {
            if (!valid(s)) continue;
            string sig = vecSignature(s);
            if (sigs.find(sig) != sigs.end()) continue;
            sigs.insert(sig);
            if (s.size() >= 2) {
                ans.push_back(s);
            }
        }
        return ans;
    }

};
