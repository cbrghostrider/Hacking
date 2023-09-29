class Solution {
    // memoization cache
    unordered_map<string, bool> cache;
    
    // creates a memoization key for the subproblem
    string signature(int left, int right, int k) {
        string ret;
        ret += "K:" + to_string(k) + ":";
        ret += "L:" + to_string(left) + ":";
        ret += "R:" + to_string(right);
        return ret;
    }
    
    bool isPalin(const string& s, int left, int right) {
        if (left >= right) return true;
        
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
    
    // Is s, a valid k-palindrome between [left, right] inclusive.
    bool isValid(const string& s, int left, int right, int k) {
        if (left >= right) return true;
        
        string sig = signature(left, right, k);
        if (cache.find(sig) != cache.end()) {return cache[sig];}
        
        if (k == 0) {
            cache[sig] = isPalin(s, left, right);
            return cache[sig];
        }
        
        bool ans = false;
        if (s[left] == s[right]) {
            ans = isValid(s, left+1, right-1, k);
        } else {
            // drop left
            bool choice1 = isValid(s, left+1, right, k-1);
            // or drop right
            bool choice2 = isValid(s, left, right-1, k-1);
            
            ans = choice1 || choice2;
        }
        
        cache[sig] = ans;
        return ans;
    }
    
public:
    // Excellent progress! Can handle much larger limits.
    // Still TLE though on big inputs.
    bool isValidPalindrome(string s, int k) {        
        bool ans = isValid(s, 0, s.size()-1, k);
        return ans;
    }
};
