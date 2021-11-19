class Solution {
public:
    // Leads to TLE: O(n^2) time.
    // Worst case test case: Russian Dolls: .....edcbaabcde....
    string removeDuplicates2(string ans) {
        bool changed = true;
        while (changed) {
            if (ans.size() <= 1) return ans;
            changed = false;
            bool include_last = false;
            string temp;
            for (int i=1; i<ans.size(); ) {
                if (ans[i-1] == ans[i]) {
                    changed = true;
                    if (i == ans.size()-2) include_last = true;
                    i += 2;
                } else {
                    temp.push_back(ans[i-1]);
                    if (i == ans.size()-1) include_last = true;
                    i += 1;
                }
            }
            if (include_last) { temp.push_back(ans[ans.size()-1]); }
            ans = temp;
        }
        return ans;
    }
    
    // O(n) time.
    string removeDuplicates(string s) {
        if (s.size() <= 1) return s;
        string ans;
        
        int ptr = 0;
        while (ptr < s.size()) {
            if (ans.empty()) {
                ans.push_back(s[ptr++]);
            } else if (ans.back() == s[ptr]) {
                ans.pop_back();
                ptr++;
            } else {
                ans.push_back(s[ptr++]);
            }
        }
        return ans;
    }
};
