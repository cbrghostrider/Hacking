class Solution {
    // DP table.
    // outer index = size of the string.
    // inner index = starting index of the string.
    vector<vector<bool>> palin;

public:
    // O(n^2) time, O(n^2) space DP solution.
    bool checkPartitioning(string s) {
        if (s.size() <= 2) return false;

        palin = vector<vector<bool>>(s.size()+1, vector<bool>(s.size(), false));

        // DP base cases, all strings of sizes 0, 1 and all strings of sizes 2.
        for (int i=0; i<s.size(); i++) {
            palin[0][i] = false;
            palin[1][i] = true;
        }
        for (int i=0; i<s.size()-1; i++) {
            if (s[i] == s[i+1]) {
                palin[2][i] = true;
            }
        }

        // DP case.
        for (int sz=3; sz<=s.size(); sz++) {
            for (int i=0; i<=s.size()-sz; i++) {
                if (palin[sz-2][i+1] && s[i] == s[i+sz-1]) {
                    palin[sz][i] = true;
                }
            }
        }        

        // Now find the answer to the posed question.
        // [0, left], [left+1, right-1], [right, s.size()-1]
        for (int left=0; left <= s.size()-3; left++) {
            for (int right=left+2; right<s.size(); right++) {
                int sz1 = left+1;
                int sz2 = (right-1) - (left+1) + 1;
                int sz3 = (s.size()-1) - right + 1;
                if (palin[sz1][0] && palin[sz2][left+1] && palin[sz3][right]) {
                    return true;
                }
            }
        }
        return false;
    }
};
