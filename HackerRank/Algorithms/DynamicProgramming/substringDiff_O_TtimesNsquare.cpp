// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// O(T*N^2) dynamic programming algorithm, and O(n^2) space
// currently TLE on some cases.... need to optimize further it seems
// Taking 10 seconds on max sized input (1500) on O3 compilation
//
// Note that using queue instead of vector as CacheElem.second makes runtime worse (25 sec)!
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <limits>
#include <utility>

using std::make_pair;
using std::pair;
using std::vector;
using std::string;

//stores for each (i, j) the -> 
//(length of longest sequence containing no more than S mismatches, 
// indices in order of places that were mismatched (string-p-based))
typedef pair<int, vector<int>> CacheElem; 

class SubstringDiff {
public:
    SubstringDiff();
    int runSubstringDiff();
private:
    void readInput();
    int S;
    string p;
    string q;
    vector<vector<CacheElem>> cache;
};

SubstringDiff::SubstringDiff() 
: S(0), p(), q(), cache() {
    readInput();
}

void SubstringDiff::readInput() {
    std::cin >> S;
    std::cin >> p;
    std::cin >> q;
}

int SubstringDiff::runSubstringDiff() {
    const int LEN = p.length();

    //stores length of match (with <=S mismatches) and indices of mismatches along this length (for p)
    cache = vector<vector<CacheElem>>(LEN+1, vector<CacheElem>(LEN+1, make_pair(0, vector<int>())));

    int maxK = 0;

    for (int i=1; i<=LEN; i++) {
        for (int j=1; j<=LEN; j++) {
            if (p[i-1] == q[j-1]) {
                cache[i][j] = make_pair(cache[i-1][j-1].first + 1, cache[i-1][j-1].second);
            } else {
                auto prevData = cache[i-1][j-1].second;
                vector<int> newvect = prevData;
                newvect.push_back(i-1);
                
                if (prevData.size() < S) { //room for another mismatch
                    cache[i][j] = make_pair(cache[i-1][j-1].first + 1, newvect);

                } else { //no room for another mismatch, get rid of oldest mismatch
                    if (S == 0) { //perfect match needed
                        cache[i][j] = make_pair(0, vector<int>());
                    } else {
                        int lastMismatchIndex = prevData[0];
                        int newlen = i - 1 - lastMismatchIndex;
                        newvect.erase(newvect.begin());
                        cache[i][j] = make_pair(newlen, newvect);
                    }
                }
            }
            int cmplen = cache[i][j].first;
            if (cmplen > maxK) {
                maxK = cmplen;
            }
        }
    }


    return maxK;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        SubstringDiff ssd;
        int ans = ssd.runSubstringDiff();
        std::cout << ans << std::endl;
    }
}
