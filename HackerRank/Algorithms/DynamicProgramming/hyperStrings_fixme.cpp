// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// The code below has a functional bug
// Consider 2 strings, "a" and "aa"
// This code considers a + aa as a different string from aa + a
// But in reality, they are the same, this leads to some double counting
// therefore only 5/10 tests pass currently
//
// I am still trying to figure out a way to avoid double counting, but, 
// without keeping all the strings that are constructed (since # of strings is too many).
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using std::string;
using std::vector;

#define MODNUM (1000000007)

typedef int Elem;

class HyperString {
public:
    HyperString();
    Elem numHyperStrings();
private:
    void readInput();
    void populateLengths();
    void populateCache();
    vector<string> strs;
    vector<Elem> lenCnt;
    vector<Elem> cache;
    int m;
};

HyperString::HyperString()
: strs(), lenCnt(), cache(), m(0) {
    readInput();
}

void HyperString::readInput() {
    int n; std::cin >> n >> m;
    for (int i=0; i<n; i++) {
        string str; std::cin >> str;
        strs.push_back(str);
    }
    lenCnt = vector<Elem>(m+1, 0);
    cache = vector<Elem>(m+1, 0);
}

void HyperString::populateLengths() {
    for (const string& s : strs) {
        if (s.length() > m) continue;
        lenCnt[s.length()]++;
    }
}

Elem HyperString::numHyperStrings() {
    populateLengths();
    populateCache();
    Elem ret = 0;
    for (const Elem& v : cache) {
        ret += v;
        ret %= MODNUM;
    }
    return ret;
}

void HyperString::populateCache() {
    cache[0] = 1;
    for (int i=1;i<=m;i++) {
        long total = 0;
        for (int j=i;j>=1; j--) {
            int cind = i-j;
            total += ((long)(lenCnt[j])) * ((long)(cache[cind]));
            total %= MODNUM;
        }
        cache[i] = total;
    }
}

int main () {
    HyperString hs;
    Elem ans = hs.numHyperStrings();
    std::cout << ans << std::endl;
}

