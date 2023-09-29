class Solution {
public:
    // O(n) time, O(1) space due to only 26 letters.
    long long numberOfSubstrings(string s) {
        unordered_map<char, int> freq, run;
        for (char ch : s) {freq[ch]++;}
        
        long long ans=0;
        for (int i=0; i<s.size(); i++) {
            int num = freq[s[i]];
            int gone = run[s[i]];
            
            // Fix start at i, we have (num-gone) positions available for end.
            ans += num-gone;
            run[s[i]]++;
        }        
        return ans;
    }
};
