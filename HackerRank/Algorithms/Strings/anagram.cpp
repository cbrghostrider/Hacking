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
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;
typedef unordered_map<char, int> t_cmap;

class Anagram {
public:
    Anagram(string s);
    int countChanges();
private:
    t_cmap constructCMap(const string& str);
    string str;
};

Anagram::Anagram(string s) 
: str(s) {
}

t_cmap Anagram::constructCMap(const string& str) {
    t_cmap ret;
    for (const char& ch: str) {
        auto it = ret.find(ch);
        if (it == ret.end()) {
            ret.insert(make_pair(ch, 1));
        } else {
            it->second += 1;
        }
    }
    return ret;
}

int Anagram::countChanges() {
    if (str.length() % 2) return -1;
    string str1 = str.substr(0, str.length()/2);
    string str2 = str.substr(str.length()/2);
    t_cmap cmap1 = constructCMap(str1);
    t_cmap cmap2 = constructCMap(str2);
    int count = 0;
    for (const pair<const char, int>& cv : cmap1) {
        auto it = cmap2.find(cv.first);
        if (it == cmap2.end()) {
            count += cv.second;
        } else if (cv.second > it->second) {
            count += cv.second - it->second;
        }
    }
    return count;
}

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        string str; std::cin >> str;
        Anagram ag(str);
        int count = ag.countChanges();
        std::cout << count << std::endl;
    }
}

