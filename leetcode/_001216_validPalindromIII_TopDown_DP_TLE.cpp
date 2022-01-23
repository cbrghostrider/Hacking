class Solution {
    // memoization cache
    unordered_map<string, bool> cache;
    
    // creates a memoization key for the subproblem
    string signature(const unordered_set<int>& removed, int next, int k) {
        string ret;
        ret += "K:" + to_string(k) + ":";
        ret += "N:" + to_string(next) + ":";
        for (int r : removed) {
            ret += to_string(r) + ":";
        }
        return ret;
    }
    
    // Is string s, with positions "removed" removed, a palindrome?
    bool isPalin(const string& s, const unordered_set<int>& removed) {
        int left=0, right=s.size()-1;
        auto forwardLeft = [&left, &s, &removed]() {
            while (left < s.size() && removed.find(left) != removed.end()) {left++;}
        };
        auto reverseRight = [&right, &s, &removed]() {
            while (right >= 0 && removed.find(right) != removed.end()) {right--;}
        };
        
        forwardLeft();
        reverseRight();
        
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++; forwardLeft();
            right--; reverseRight();
        }
        
        return true;
    }
    
    // Is s, with "removed" positions removed, a k palindrome
    bool isValid(const string& s, unordered_set<int> removed, int next, int k) {
        string sig = signature(removed, next, k);
        if (cache.find(sig) != cache.end()) {return cache[sig];}
        
        if (next == s.size() || k == 0) {
            cache[sig] = isPalin(s, removed);
            return cache[sig];
        }
                
        // keep next
        bool choice1 = isValid(s, removed, next+1, k);
        
        // drop next        
        removed.insert(next);
        bool choice2 = isValid(s, removed, next+1, k-1);
                        
        cache[sig] = choice1 || choice2;
        return cache[sig];
    }
    
public:
    //
    // Solution is functionally correct, but runs into TLE for bigger inputs.
    //
    bool isValidPalindrome(string s, int k) {        
        bool ans = isValid(s, {}, 0, k);
        return ans;
    }
};
