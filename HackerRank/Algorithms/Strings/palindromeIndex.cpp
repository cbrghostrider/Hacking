// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int getPalindromeIndex(const string& str) {
    int indexchosen, indexother;
    int cnt=0;
    int pl=0, pr = str.length()-1;
    while (pl<pr) {
        if (str[pl] == str[pr]) {
            pl++;
            pr--;
            continue;
        }
        if (cnt != 0) {
            return indexother;
        }
        cnt++;
        if (str[pr] == str[pl+1]) {
            indexchosen = pl;
            indexother = pr;
            pl += 2;
            pr--;
        } else {
            indexchosen = pr;
            indexother = pl;
            pl++;
            pr -= 2;
        }
    }
    if (cnt != 0) return (cnt == 1 ? indexchosen : indexother);
    return -1;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        string str; std::cin >> str;
        int pind = getPalindromeIndex(str);
        std::cout << pind << std::endl;
    }
}

