class Solution {
    // memoization cache
    unordered_map<string, bool> cache;
    
    // creates a memoization key for the subproblem
    string signature(const string& s, int next, int k) {
        string ret;
        ret += "K:" + to_string(k) + ":";
        ret += "N:" + to_string(next) + ":";
        ret += "S:" + s;
        return ret;
    }
    
    bool isPalin(const string& s) {
        if (s.size() == 0) return true;
        
        int left=0, right=s.size()-1;
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
    
    // Is s, with "removed" positions removed, a k palindrome
    bool isValid(const string& s, int next, int k) {
        string sig = signature(s, next, k);
        if (cache.find(sig) != cache.end()) {return cache[sig];}
        
        if (next == s.size() || k == 0) {
            cache[sig] = isPalin(s);
            return cache[sig];
        }
                
        // keep next
        bool choice1 = isValid(s, next+1, k);
        
        // drop next        
        string s2 = s.substr(0, next) + s.substr(next+1);
        bool choice2 = isValid(s2, next, k-1);
                        
        cache[sig] = choice1 || choice2;
        return cache[sig];
    }
    
public:
    // Faster then before, clearing a few more test cases.
    // But still TLE.
    bool isValidPalindrome(string s, int k) {        
        bool ans = isValid(s, 0, k);
        return ans;
    }
};
