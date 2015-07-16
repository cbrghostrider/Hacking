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
#include <unordered_map>
#include <utility>
using namespace std;

class AnagramPairs {
public:
    AnagramPairs(string s) : str(s) {}
    int findAPCount();
private:
    string str;
};

int AnagramPairs::findAPCount() {
    int ctr=0;
    unordered_map<string, int> strMap;
    for (int i=0;i<str.length(); i++) {
        for (int j=i; j >=0; j--) {
            int cnt = i - j + 1;
            string cs = str.substr(j, cnt);
            std::sort(cs.begin(), cs.end());
            auto it = strMap.find(cs);
            if (it == strMap.end()) {
                strMap.insert(make_pair(cs, 1));
            } else {
                ctr += it->second;
                it->second += 1;
            }
        }
    }
    return ctr;
}

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        string str; std::cin >> str;
        AnagramPairs ap(str);
        int count = ap.findAPCount();
        std::cout << count << std::endl;
    }
    return 0;
}

