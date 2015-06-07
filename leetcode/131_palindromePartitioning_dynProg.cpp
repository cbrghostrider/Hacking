// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//Successful execution, online judge accepted.
class Solution {
    typedef vector<vector<string>> PalPart;
    
    bool isPalindrome_(const string& s) {
        for (int i=0; i<s.length()/2; i++) {
            if (s[i] != s[s.length()-1-i]) return false;
        }
        return true;
    }
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> pp;
        if (s.length() == 0) return pp;
        
        //dynamic programming cache
        PalPart cache[s.size()];
        
        //base case
        vector<string> ret;
        ret.push_back(s.substr(0, 1));
        pp.push_back(ret);
        cache[0] = pp;
        pp.clear();
        
        //partition s
        for (int p=1; p<s.size(); p++) {
            string check = s.substr(0, p+1);
            if (isPalindrome_(check)) {
                vector<string> strv;
                strv.push_back(check);
                pp.push_back(strv);
            } 
            for (int ind=p; ind > 0; ind--) {
                string ssLhs = s.substr(0, ind);
                string ssRhs = s.substr(ind, p+1-ind);
                if (!isPalindrome_(ssRhs)) continue;
                PalPart pplhs = cache[ind-1];
                for (vector<string>& pals : pplhs) {
                    vector<string> part = pals;
                    part.push_back(ssRhs);
                    pp.push_back(part);
                }
            }
            cache[p] = pp;
            pp.clear();
        }
        
        return cache[s.size()-1];
    }
};
