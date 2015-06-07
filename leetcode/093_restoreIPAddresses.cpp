// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    bool isValid(string s) {
        return (!((s.length() == 0) || (s.length() > 3) || (s.length() >= 2 && s[0] == '0') || (stoi(s) > 255)));
    }
public:
    vector<string> restoreChunk(string s, int chunkNo) {
        if (chunkNo == 4) {
            if (!isValid(s)) return vector<string>();   //impossible
            return vector<string>(1, s);                //can't subdivide anymore
        }
        vector<string> retval;
        for (int i=1; i<=3 && i < s.length(); i++) {    //try 1, 2, or 3 digit combos
            string myChunk = s.substr(0, i);
            if (!isValid(myChunk)) continue;
            vector<string> recurse = restoreChunk(s.substr(i), chunkNo+1);
            for (string& rec : recurse) {
                retval.push_back(myChunk + "." + rec);
            }
        }
        return retval;
    }
    vector<string> restoreIpAddresses(string s) {
        return restoreChunk(s, 1);
    }
};
