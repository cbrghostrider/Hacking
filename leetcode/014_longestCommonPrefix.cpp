// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    int minLength(vector<string>& strs) {
        if (strs.size() == 0) return 0;
        int min=std::numeric_limits<int>::max();
        for (int i=0; i<strs.size(); i++) {
            if (strs[i].length() < min) min = strs[i].length();
        }
        return min;
    }
    bool matchAtMark(vector<string>& strs, int mark) {
        for (int i=1; i<strs.size(); i++) {
            if (strs[i][mark] != strs[0][mark]) return false;
        }
        return true;
    }
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0) return "";
        int mark=0;
        int minlen = minLength(strs);
        for (mark=0; mark < minlen; mark++) {
            if (!matchAtMark(strs, mark)) break;
        }
        return strs[0].substr(0, mark);
    }
};
