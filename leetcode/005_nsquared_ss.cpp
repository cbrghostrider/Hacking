class Solution {
public:

    // if l == r, check if palindrome with odd # of letters
    // else check if palindrome with even # of letters
    string getPalindromeAtCenter(const string& s, int l, int r) {
        assert(l == r || l+1 == r);
        
        if (r >= s.size() || s[l] != s[r]) {
            return string("");
        }
        
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            l--;
            r++;
        }
        
        //when we exited loop, either we were out of bounds, or last thing didn't match
        //in either case, we need to fix up the indices
        l++;
        r--;
        return s.substr(l, r-l+1);
    }
    
    string longestPalindrome(string s) {
        string longest;
        for (int i=0; i<s.size(); i++) {
            //get palindrome substr centered at i
            string oddCand = getPalindromeAtCenter(s, i, i);
            if (oddCand.size() > longest.size()) {
                longest = oddCand;
            }
            
            //get palindrome substr centered between i and i+1
            string evenCand = getPalindromeAtCenter(s, i, i+1);
            if (evenCand.size() > longest.size()) {
                longest = evenCand;
            }
        }
        return longest;
    }
};

