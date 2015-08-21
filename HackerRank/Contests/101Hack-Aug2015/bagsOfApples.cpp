// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using std::pair;
using std::make_pair;
using std::vector;

class Apples {
public:
    Apples();
    int computeMaxSale();
private:
    void readInput();
    int computeMaxSale1();
    int computeMaxSale2();
    vector<int> apples;
    vector<pair<int, int>> mod0;
    vector<pair<int, int>> mod1;
    vector<pair<int, int>> mod2;
    int cumusum;
};

Apples::Apples() 
: apples(), mod0(), mod1(), mod2(), cumusum(0) {
    readInput();
}

void Apples::readInput() {
    int n; std::cin >> n;
    for (int i=0; i<n; i++) {
        int apple; std::cin >> apple;
        apples.push_back(apple);
        cumusum += apple;
    }
}

int Apples::computeMaxSale() {
    for (int i=0; i<apples.size(); i++) {
        if ((apples[i] % 3) == 1) { 
            mod1.push_back(make_pair(apples[i], i));
        } else if ((apples[i] % 3) == 2) { 
            mod2.push_back(make_pair(apples[i], i));
        } else {
            mod0.push_back(make_pair(apples[i], i));
        }
    }

    std::sort(mod0.begin(), mod0.end(), [] (const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
        return (lhs.first < rhs.first);
    });
    std::sort(mod1.begin(), mod1.end(), [] (const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
        return (lhs.first < rhs.first);
    });
    std::sort(mod2.begin(), mod2.end(), [] (const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
        return (lhs.first < rhs.first);
    });

    int sale1 = computeMaxSale1();
    int sale2 = computeMaxSale2();
    return std::max(sale1, sale2);
}

int Apples::computeMaxSale1() {
    int count = 0;

    for (int i=0; i<mod0.size(); i++) { count += mod0[i].first;}

    int mod1take = (mod1.size() / 3) * 3;
    int mod1drop = mod1.size() - mod1take;
    for (int i=mod1.size()-1; i>=mod1drop; i--) { count += mod1[i].first;}

    int mod2take = (mod2.size() / 3) * 3;
    int mod2drop = mod2.size() - mod2take;
    for (int i=mod2.size()-1; i>=mod2drop; i--) { count += mod2[i].first;}

    int mincnt = std::min(mod1drop, mod2drop);
    for (int i=mincnt-1, m1c=mod1drop-1, m2c=mod2drop-1; i>=0; i--, m1c--, m2c--) { 
        count += (mod1[m1c].first + mod2[m2c].first); 
    }

    return count;
}

int Apples::computeMaxSale2() {
    int count = 0;

    for (int i=0; i<mod0.size(); i++) { count += mod0[i].first;}

    int mincnt = std::min(mod1.size(), mod2.size());
    for (int i=mincnt-1, m1c=mod1.size()-1, m2c=mod2.size()-1; i>=0; i--, m1c--, m2c--) { 
        count += (mod1[m1c].first + mod2[m2c].first); 
    }

    int maxcnt = std::max(mod1.size(), mod2.size());
    int remcnt = maxcnt - mincnt;
    auto remapples = (mod1.size() > mod2.size()) ? mod1 : mod2;

    for (int i=remcnt-1; i>=0 && (i/3)>0; i-=3) {
        count += remapples[i].first;
        count += remapples[i-1].first;
        count += remapples[i-2].first;
    }
    return count;
}


int main() {
    Apples a;
    int ans = a.computeMaxSale();
    std::cout << ans << std::endl;
}
