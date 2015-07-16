// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <string>

using std::string;
using std::unordered_set;

typedef unordered_set<char> cset;

cset getCSet(const string& str) {
    cset ret;
    for (const char& ch : str) {ret.insert(ch);}
    return ret;
}

bool isCommonSS(const string& str1, const string& str2) {
    cset c1 = getCSet(str1);
    cset c2 = getCSet(str2);
    for (const char& ch : c1) {
        if (c2.find(ch) != c2.end()) return true;
    }
    return false;
}

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        string str1, str2; 
        std::cin >> str1;
        std::cin >> str2;
        bool ans = isCommonSS(str1, str2);
        std::cout << (ans ? "YES" : "NO") << std::endl;
    }
}
