// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    unordered_map<char, int> chfreq;
    char oddCh;
    int numOdds = 0;
    
    void populateFreqMap(const string& s) {
        for (const char& ch : s) {
            auto it = chfreq.find(ch);
            if (it == chfreq.end()) {
                chfreq.insert(make_pair(ch, 1));
            } else {
                chfreq[ch]++;
            }
        }
    }
    
    bool canPermutePalindrome(string s) {
        for (const pair<char, int>& cip : chfreq) {
            if (cip.second % 2) {
                oddCh = cip.first;
                numOdds++;
            }
        } 
        return (numOdds <= 1);
    }
    
    vector<string> getPermutations(unordered_map<char, int> cf) {
       if (cf.size() == 0) return vector<string>(1, string(""));
       vector<string> retval;
       for (const pair<char, int>& cip : cf) {
           unordered_map<char, int> ncf = cf;
           auto it = ncf.find(cip.first);
           if (it->second == 1) {
               ncf.erase(it);
           } else {
               it->second -= 1;
           }
           vector<string> recurse = getPermutations(ncf);
           for (string& s : recurse) {
               s.push_back(cip.first);
               retval.push_back(s);
           }
       }
       return retval;
    }
public:
    vector<string> generatePalindromes(string s) {
        populateFreqMap(s);
        if (!canPermutePalindrome(s)) return vector<string>();
        
        if (numOdds) {
            if (chfreq[oddCh] == 1) {
                chfreq.erase(chfreq.find(oddCh));
            } else {
                chfreq[oddCh]--;
            }
        }
        
        unordered_map<char, int> cf = chfreq;
        for (pair<const char, int>& cip : cf) { cip.second /= 2; }
        
        vector<string> perms = getPermutations(cf);
        vector<string> retval;
        for (const string& str : perms) {
            string rev = str;
            std::reverse(rev.begin(), rev.end());
            string mid = (numOdds ? string(1, oddCh) : "");
            retval.push_back(str + mid + rev);
        }
        return retval;
    }
};
