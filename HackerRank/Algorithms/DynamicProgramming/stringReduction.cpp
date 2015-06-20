// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <string>
#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>
#include <limits>
#include <algorithm>

using std::vector;
using std::string;
using std::unordered_map;
using std::pair;
using std::make_pair;

class StringReduction {
private:
    unordered_map<string, char> reductions;
    unordered_map<string, vector<string>> cache; 

    string reduce(string lhs, char rhs) {
        if (lhs[lhs.size()-1] == rhs) return lhs + string(1, rhs);
        auto it = reductions.find(string(1, lhs[lhs.size()-1]) + string(1, rhs));
        return lhs.substr(0, lhs.size()-1) + string(1, it->second);
    }

    void cleanCandidates(vector<string>& candidates) {
        std::sort(candidates.begin(), candidates.end());
        auto it = std::unique(candidates.begin(), candidates.end());
        candidates.erase(it, candidates.end());

        std::sort(candidates.begin(), candidates.end(), [] (const string& lhs, const string& rhs) -> bool {
            return (lhs.length() < rhs.length());
        });
        int minlen = candidates[0].length();
        it = std::find_if_not(candidates.begin(), candidates.end(), [minlen] (const string& chk) -> bool {
            return (chk.length() <= minlen+2);
        });
        candidates.erase(it, candidates.end());
    }
    
    vector<string> stringReduction(string str) {
        auto cit = cache.find(str);
        if (cit != cache.end()) {
            return cit->second;
        }

        if (str.length() == 1) {
            vector<string> res(1, str); 
            cache.insert(make_pair(str, res));
            return res;
        } else if (str.length() == 2) {
            auto rit = reductions.find(str);
            string resstr = (rit == reductions.end()) ? str  : string(1, rit->second);
            vector<string> res(1, resstr);
            cache.insert(make_pair(str, res));
            return res;
        }

        char mylast       = str[str.length() - 1];
        char mysecondlast = str[str.length() - 2];
        vector<string> candidates;

        //option 0: Reduce from [0, len-1] and try to reduce with last one if possible
        string checkstr = str.substr(0, str.length()-1);
        vector<string> recurseRes0 = stringReduction(checkstr);
        for (string& recstr : recurseRes0) {
            if (recstr == checkstr) {
                candidates.push_back(str);
            } else {
                vector<string> res1 = stringReduction(recstr + string(1, mylast));
                candidates.insert(candidates.end(), res1.begin(), res1.end());
            }
        }

        //option 1: Reduce from [0, len-2] and try to reduce with last two if possible
        checkstr = str.substr(0, str.length()-2);
        vector<string> recurseRes1 = stringReduction(checkstr);
        for (string& recstr : recurseRes1) {
            if (recstr == checkstr) {
                candidates.push_back(str);
            } else {
                vector<string> res1 = stringReduction(recstr + string(1, mysecondlast) + string(1, mylast));
                candidates.insert(candidates.end(), res1.begin(), res1.end());
            }
        }

        cleanCandidates(candidates);

        if (mylast == mysecondlast) { //this is the only option in this case
            cache.insert(make_pair(str, candidates));
            return candidates;
        }

        //case (mylast != mysecondlast)
        char reduced = reductions.find(string(1, mysecondlast) + string(1, mylast))->second;

        //option 2: try to reduce reduced [0, len-2], with reduction of last 2
        vector<string> recurseRes2 = stringReduction(str.substr(0, str.length()-2));
        for (string& recstr : recurseRes2) {
            vector<string> res2 = stringReduction(recstr + string(1, reduced));
            candidates.insert(candidates.end(), res2.begin(), res2.end());
        }
        
        //option 3: Try to reduce [0, len-2] with reduction of last 2
        //take the smallest option
        vector<string> res3 = stringReduction(str.substr(0, str.length() - 2) + string(1, reduced));
        candidates.insert(candidates.end(), res3.begin(), res3.end());

        cleanCandidates(candidates);

        cache.insert(make_pair(str, candidates));
        return candidates;
    }

public:

    StringReduction() : reductions(), cache() {
        reductions.insert(make_pair("ab", 'c'));
        reductions.insert(make_pair("ba", 'c'));
        reductions.insert(make_pair("ac", 'b'));
        reductions.insert(make_pair("ca", 'b'));
        reductions.insert(make_pair("bc", 'a'));
        reductions.insert(make_pair("cb", 'a'));
    }

    int stringReduce(string str) {
        vector<string> candidates = stringReduction(str);
        return candidates[0].length();
    }

};


int main() {
    int res, t, i;
    std::cin >> t;
    char a[100001];
    for (i=0;i<t;i++) {
        string str;
        std::cin >> str;
        StringReduction sr;
        res=sr.stringReduce(str);
        std::cout << res << std::endl;
    }
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
