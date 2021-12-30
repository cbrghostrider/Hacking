class Solution {
    // Check if, starting at hptr, needle constantly repeats in haystack
    // The last repeat can be a partial match
    // returns number of matches (including partial match)
    int matchesPeriodic(const string& haystack, int hptr, const string& needle) {
        int ctr=0;
        while (hptr < haystack.size()) {
            for (int i=0; i<needle.size() && hptr<haystack.size(); i++) {
                if (needle[i] != haystack[hptr++]) return -1;
            }
            ctr++;
        }
        return ctr;
    }
    
    // check if, starting from nptr to the end, 
    // the (partial) needle matches the start of the haystack
    bool suffixMatch(const string& haystack, const string& needle, int nptr) {
        int hptr=0;
        for (int i=nptr; i<needle.size() && hptr<haystack.size(); i++) {
            if (needle[i] != haystack[hptr++]) return false;
        }
        return true;
    }
public:
    // O(mn) time, O(1) space.
    int repeatedStringMatch(string a, string b) {        
        int icheck = matchesPeriodic(b, 0, a);
        if (icheck != -1) return icheck;
        
        int fcheck=-1;
        
        if (a.size() > b.size()) {  // check lined up at the start
            fcheck = matchesPeriodic(b, 0, a.substr(a.size()-b.size()));
        } else if (b.size() % a.size()) {  // check lined up at the end
            bool ficheck = suffixMatch(b, a, a.size() - b.size()%a.size());
            fcheck = matchesPeriodic(b, b.size()%a.size(), a);
            if (fcheck != -1 && ficheck == true) {
                fcheck += 1;
            } else {
                fcheck = -1;
            }
        }
        
        int delta = a.size()-1;
        for (int d=delta; d >=1; d--) {
            bool picheck = suffixMatch(b, a, a.size()-d);
            if (!picheck) continue;
            int pcheck = matchesPeriodic(b, d, a);
            if (pcheck == -1) continue;
            return 1 + pcheck;
        }
        return -1;
    }    
};
