class Solution {
    vector<vector<int>> first_occurrence;
    
    // Recurrence:
    // for indices i, j
    // lps(i, j) = max(c1, c2)
    //    c1 ---> lps(i, j-1)
    //    c2 ---> 2 + lps(first_occurrence[s[j]]+1, j-1)
    //
    // Instead of indices, we can also re-write it in terms of start index and size, which is easier to iterate over
    
    // returns the first occurrence of char ch at or greater than index.
    int firstOccurrence(int index, char ch) {
        return first_occurrence[index][ch-'a'];
    }
public:
    int longestPalindromeSubseq(string s) {
        first_occurrence = vector<vector<int>>(s.size(), vector<int>(26, -1));
        vector<int> mappings(26, -1);
        for (int i=s.size()-1; i>=0; i--) {
            mappings[s[i] - 'a'] = i;
            first_occurrence[i] = mappings;
        }
        
        // longest palindromic subsequence for: (start index, size)
        vector<vector<int>> dp(s.size(), vector<int>(s.size()+1, 0));
        
        // Base cases.
        for (int i=0; i<s.size(); i++) {
            dp[i][1] = 1;
        }
        
	// O(n^2) time.
        for (int sz=2; sz<=s.size(); sz++) {
            for (int i=0; i<=s.size()-sz; i++) {
                int j = i+sz-1;  // end index
                int c1 = dp[i][sz-1], c2=1;
                char ch = s[j];
                int fo = firstOccurrence(i, ch);
                
                if (fo == j) {
                    c2 = 1;
                } else if (fo == j-1) {  // fo occurs one before end i.e. string ends in [....'ch''ch']
                    c2 = 2;              // we do this to avoid dp indexing with sz<1 (see next clause)
                } else {
                    int new_sz = j-1-fo;
                    c2 = 2 + dp[fo+1][new_sz];
                }
                int val = std::max(c1, c2);
                dp[i][sz] = std::max(c1, c2);
            }
        }
        return dp[0][s.size()];
    }
};
