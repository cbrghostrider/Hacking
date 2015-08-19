// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    unordered_map<char, char> strobos;
    void populateStrobos() {
        strobos.insert(make_pair('0', '0'));
        strobos.insert(make_pair('1', '1'));
        strobos.insert(make_pair('6', '9'));
        strobos.insert(make_pair('8', '8'));
        strobos.insert(make_pair('9', '6'));
    }
public:

    vector<string> findStrobogrammatic_(int n) {
        vector<string> retval = {"1", "6", "8", "9"};
        for (int i=2; i<=n; i++) {
            vector<string> local = retval;
            retval.clear();
            for (const string& str : local) {
                for (auto elem : strobos) {
                    retval.push_back(str + string(1, elem.first));
                }
            }
        }
        return retval;
    }
    
    vector<string> findStrobogrammatic(int n) {
        populateStrobos();

        vector<string> mids = {"0", "1", "8"};
        vector<string> retval;
        if (n <= 0) return retval;
        if (n == 1) return mids;
        
        vector<string> recStrobos = findStrobogrammatic_(n/2);
        if (n % 2) { //if n is odd
            for (const string& rec : recStrobos) {
                for (const string& m : mids) {
                    retval.push_back(rec + m);
                }
            }
        } else {
            retval = recStrobos;
        }
        int limit = n/2-1;
        for (string& rs : retval) {
            for (int i=limit; i>=0; i--) {
                rs.push_back(strobos[rs[i]]);
            }
        }
        return retval;
    }
};
