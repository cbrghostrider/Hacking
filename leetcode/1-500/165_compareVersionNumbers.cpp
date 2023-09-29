// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    vector<string> tokenize(string version) {
        vector<string> retval;
        string last = std::accumulate(version.begin(), version.end(), string(), [&retval] (const string& acc, const char& ch) -> string {
            if (ch == '.') {
                retval.push_back(acc);
                return "";
            }
            return acc + string(1, ch);
        });
        retval.push_back(last);
        return retval;
    }
    void dropTrailingZeros(vector<string>& vec) {
        bool change = true;
        while (vec.size() && change) {
            change = false;
            string check=vec[vec.size()-1];
            bool allZeros = std::accumulate(check.begin(), check.end(), true, [] (const bool& acc, const char& ch) -> bool {
                return (acc && (ch == '0'));
            });
            if (allZeros) {
                vec.pop_back();
                change = true;
            }
        }
    }
public:
    int compareVersion(string version1, string version2) {
        vector<string> tv1 = tokenize(version1);
        vector<string> tv2 = tokenize(version2);
        dropTrailingZeros(tv1);
        dropTrailingZeros(tv2);
        for (int v1=0, v2=0; v1<tv1.size() && v2 < tv2.size(); v1++, v2++) {
            int v1i = stoi(tv1[v1]);
            int v2i = stoi(tv2[v2]);
            if (v1i > v2i) return 1;
            if (v1i < v2i) return -1;
        }
        if (tv1.size() == tv2.size()) return 0;
        if (tv1.size() >  tv2.size()) return 1;
        return -1;
    }
};
