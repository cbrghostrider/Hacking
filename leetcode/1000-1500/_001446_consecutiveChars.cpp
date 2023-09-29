class Solution {
public:
    
    // This solves a different problem.
    // This gives the length of the longest substr that has only unique chars.
    // Left here because it is interesting enough.
    // O(n) time.
    int maxPower2(string s) {
        if (s.size() <= 1) return s.size();
        
        int l_ptr=0, r_ptr=0;
        unordered_set<char> found;
        int max = 0;
        
        while (r_ptr < s.size()) {
            while (r_ptr < s.size() && 
                   found.find(s[r_ptr]) == found.end()) {
                found.insert(s[r_ptr++]);
            }
            int len = r_ptr - l_ptr;
            if (max < len) {max = len;}
            if (r_ptr == s.size()) break;
            
            while (s[l_ptr] != s[r_ptr]) {
                found.erase(s[l_ptr++]);
            }
            if (l_ptr != r_ptr) found.erase(s[l_ptr++]);
        }
        return max;
    }
    
    // This solution is for the stated problem.
    // O(n) time.
    int maxPower(string s) {
        int max = 0;
        int l_ptr=0;
        for (int r_ptr=0; r_ptr<s.size(); r_ptr++) {
            if (s[l_ptr] == s[r_ptr]) { continue; }
            int len = r_ptr-l_ptr;    
            if (len > max) max = len;
            l_ptr = r_ptr;
        }
        if (s.size() - l_ptr > max) {max = s.size() - l_ptr;}
        return max;
    }
};
