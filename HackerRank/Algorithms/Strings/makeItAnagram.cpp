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
#include <map>
#include <utility>

using namespace std;

typedef map<char, int> t_cmap;

t_cmap getCMap(const string& str) {
    t_cmap ccount;
    for (const char& ch : str) {
        auto it = ccount.find(ch);
        if (it == ccount.end()) {
            ccount.insert(make_pair(ch, 1));
        } else {
            it->second += 1;
        }
    }
    return ccount;
}

int findMinDeletions(string str1, string str2) {
    t_cmap ccount1 = getCMap(str1);
    t_cmap ccount2 = getCMap(str2);
    map<char, int> symdiffset, interset;
    std::set_symmetric_difference(ccount1.begin(), ccount1.end(), ccount2.begin(), ccount2.end(), 
                                  std::inserter(symdiffset, symdiffset.end()), 
                                  [] (const pair<const char, int>& lhs, const pair<const char, int>& rhs) -> bool {
        return (lhs.first < rhs.first);
    });
    std::set_intersection(ccount1.begin(), ccount1.end(), ccount2.begin(), ccount2.end(), 
                                  std::inserter(interset, interset.end()), 
                                  [] (const pair<const char, int>& lhs, const pair<const char, int>& rhs) -> bool {
        return (lhs.first < rhs.first);
    });
    int count = 0;
    for (const pair<const char, int>& cv : symdiffset) { count += cv.second; }
    for (const pair<const char, int>& cv : interset) {
        auto c1it = ccount1.find(cv.first);
        auto c2it = ccount2.find(cv.first);
        count += abs(c1it->second - c2it->second);
    }
    return count;
}

int main() {
    string str1, str2;
    std::cin >> str1 >> str2;
    int ans = findMinDeletions(str1, str2);
    std::cout << ans << std::endl;
}

