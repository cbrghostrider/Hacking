// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------

//integers can only be up to 10 digits
#define INTLENLIMIT (10) 

class Solution {
    unordered_map<char, char> strobos;
    
    void populateStrobos() {
        strobos.insert(make_pair('0', '0'));
        strobos.insert(make_pair('1', '1'));
        strobos.insert(make_pair('6', '9'));
        strobos.insert(make_pair('8', '8'));
        strobos.insert(make_pair('9', '6'));
    }

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
    
    //how many strobos that are x-digit numbers
    int numStrobos(int xdigitnum) {
        if (xdigitnum <= 0) return 0;
        if (xdigitnum == 1) return 3; //0, 1, 8
        int initialDigs = xdigitnum/2;
        int initCandidates = pow(5, initialDigs-1) * 4;  //0, 1, 6, 8, 9 as digits other than first, 1, 6, 8, 9 as first digits
        int oddCandidates = initCandidates * 3; //0, 1, 8 as middle digits
        return ((xdigitnum % 2) ? oddCandidates : initCandidates);
    }
public:
    int strobogrammaticInRange(string low, string high) {
        populateStrobos();
        
        if (stoll(low) <= 0) low = "0";
        if (stoll(high) < 0) return 0;
        if (stoll(low) > stoll(high)) return 0;
        if (stoll(high) == 0) return 1;
        if (low.length() > high.length()) return 0;
        
        long long lown = stoll(low);
        long long highn = stoll(high);
        int count = 0;
        if (low.length() == high.length()) { //just generate the numbers and filter them
            vector<string> mystrobos = findStrobogrammatic(low.length());
            for (const string& str : mystrobos) {
                if (stoll(str) >= lown && stoll(str) <= highn) count++;
            }
            return count;
        }
        
        //count boundaries for low and high
        vector<string> lostrobos = findStrobogrammatic(low.length());
        for (const string& str : lostrobos) { if (stoll(str) >= lown) count++;}
        vector<string> histrobos = findStrobogrammatic(high.length());
        for (const string& str : histrobos) { if (stoll(str) <= highn) count++;}
        
        for (int len = low.length()+1; len < high.length(); len++) {
            count += numStrobos(len);
        }
        return count;
    }
};
