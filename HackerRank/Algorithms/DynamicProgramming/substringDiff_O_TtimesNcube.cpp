// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// O(T*N^3) dynamic programming algorithm, and O(n^2) space
// currently TLE on many cases.... need to optimize
// Taking 69 seconds on max sized input (1500) on O3 compilation
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <limits>

using std::vector;
using std::string;

class SubstringDiff {
public:
    SubstringDiff();
    int runSubstringDiff();
private:
    void readInput();
    void allocCache(int LEN);
    void freeCache(int LEN);
    int S;
    string p;
    string q;
    int ***cache;
};

SubstringDiff::SubstringDiff() 
: S(0), p(), q(), cache(NULL) {
    readInput();
}

void SubstringDiff::readInput() {
    std::cin >> S;
    std::cin >> p;
    std::cin >> q;
}

void SubstringDiff::allocCache(int LEN) {
    cache = new int**[2];
    cache[0] = new int*[LEN+1];
    cache[1] = new int*[LEN+1];
    for (int i=0; i<2; i++) {
        for (int j=0; j<=LEN; j++) {
            cache[i][j] = new int[LEN+1];
        }
    }
}

void SubstringDiff::freeCache(int LEN) {
    for (int i=0; i<2; i++) {
        for (int j=0; j<=LEN; j++) {
            delete [] cache[i][j];
        }
    }
    delete [] cache[0];
    delete [] cache[1];
    delete [] cache;
}

int SubstringDiff::runSubstringDiff() {
    const int LEN = p.length();
    allocCache(LEN);

    int maxK = 0;

    for (int i=0; i<=LEN; i++) {
        for (int j=0; j<=LEN; j++) {
            cache[0][j][0] = 0; //base cases
            for (int k=1; k<=LEN; k++) {
                if (i < k || j < k) continue; //infinite distance, can't consume strings
                cache[1][j][k] = cache[0][j-1][k-1];
                if (p[i-1] != q[j-1] && cache[1][j][k] != std::numeric_limits<int>::max()) { //0-indexing the strings
                    cache[1][j][k] += 1;
                }
                if (cache[1][j][k] <= S && k > maxK) {
                    maxK = k;
                }
            }
        }
        int** temp = cache[0];
        cache[0] = cache[1];
        cache[1] = temp;
    }

    freeCache(LEN);

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


