class Solution {
    
    // Only handles plus/minus.
    long calculatorPM(const vector<string>& nums, const string& ops) {
        long val = stol(nums[0]);
        
        for (int i=1, j=0; i<nums.size(); i++, j++) {
            long num = stol(nums[i]);
            if (ops[j] == '+') {
                val += num;
            } else {
                val -= num;
            }
        }
        return val;
    }
    
    // handles plus/minus/multiply.
    long calculator(const string& computation) {
        vector<string> inum;
        string iops;
        
        int s_ptr=computation.find_first_of("+-*", 0);
        int len = s_ptr == string::npos ? computation.size() : s_ptr;
        string val = computation.substr(0, len);
        inum.push_back(val);
        if (s_ptr == string::npos) {
            return stol(val);
        }
        
        while (s_ptr < computation.size() && s_ptr != string::npos) {
            char op = computation[s_ptr];
            s_ptr++;
            int pos = computation.find_first_of("+-*", s_ptr);
            int len = pos == string::npos ? computation.size() - s_ptr : pos - s_ptr;
            string val = computation.substr(s_ptr, len);
            
            if (op == '*') {
                long pval = stol(inum.back());
                inum.pop_back();
                pval *= stol(val);
                inum.push_back(to_string(pval));
            } else {
                iops.push_back(op);
                inum.push_back(val);
            }
            if (pos == -1) break;  
            s_ptr = pos;
        }
        
        return calculatorPM(inum, iops);
    }
    
    string stripLeadingZeros(const string& pre) {
        int zptr=0;        
        for (; zptr<pre.size()-1; zptr++) {
            if (pre[zptr] != '0') break;
        }
        return pre.substr(zptr);        
    }
    
    unordered_set<string> getCalcs(const string& num) {
        if (num.size() == 0) return {""};
        if (num.size() == 1) return {num};
        
        unordered_set<string> ans;
        for (int i=1; i<num.size(); i++) {
            string pre = num.substr(0, i);
            int zptr=0;
            for (; zptr<pre.size()-1; zptr++) {
                if (pre[zptr] != 0) break;
            }
            pre = stripLeadingZeros(pre);
            string post = num.substr(i);
            
            unordered_set<string> postCalcs = getCalcs(post);
            for (const string& pc : postCalcs) {
                ans.insert(pre + "+" + pc);
                ans.insert(pre + "-" + pc);
                ans.insert(pre + "*" + pc);
            }            
        }
        
        ans.insert(stripLeadingZeros(num));
        return ans;
    }
    
public:
    // Does a simple brute force by generating all combos.
    // This solution currently gets a TLE.
    vector<string> addOperators(string num, int target) {
        unordered_set<string> all_calcs = getCalcs(num);
        vector<string> ans;
        for (const string& comp : all_calcs) {
            long val = calculator(comp);
            if (val == target) {
                ans.push_back(comp);
            }
        }
        return ans;
    }
};
