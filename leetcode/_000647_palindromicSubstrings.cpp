class Solution {
public:
    // Recurrence:
    // palindrome(i, sz) = 
    //   str[i] == str[i+sz-1] && palindrome(i+1, sz-2)
    // O(n*n) space, O(n*n) time.
    int countSubstrings(string s) {
        if (s.empty()) return 0;
        const int N=s.size();
        // string starting at index "index", of size "size", is it a palindrome?
        vector<vector<bool>> palins(N, vector<bool>(N+1, false));
        
        // Base cases, sz=0, 1, 2
        int count = N;
        for (int i=0; i<N; i++) {
            palins[i][0] = palins[i][1] = true;
            if (i != N-1) {
                if (s[i] == s[i+1]) {
                    count++;
                    palins[i][2] = true;
                }
            }
        }
        
        for (int sz=3; sz<=N; sz++) {
            for (int i=0; i<=N-sz; i++) {
                palins[i][sz] = (s[i] == s[i+sz-1] && palins[i+1][sz-2]);
                if (palins[i][sz]) {count++;}
            }
        }
        return count;
    }
};
