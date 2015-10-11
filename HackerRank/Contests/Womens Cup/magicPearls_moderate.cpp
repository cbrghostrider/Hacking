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
#include <queue>
using namespace std;

typedef long long Cost;

Cost MODNUM = 1000000007;

struct HeapCmp {
    bool operator() (const Cost& lhs, const Cost& rhs) {
        return (lhs > rhs);
    }
};

int main() {
    int n; std::cin >> n;
    priority_queue<Cost, vector<Cost>, HeapCmp> pearls;
    for (int i=0; i<n; i++) {
        Cost pearl;
        std::cin >> pearl;
        pearls.push(pearl);
    }
    
    Cost total = 0;
    
    while (pearls.size() > 1) {
        Cost p1 = pearls.top(); pearls.pop();
        Cost p2 = pearls.top(); pearls.pop();
        Cost p = p1 + p2;
        total += p;
        total %= MODNUM;
        p %= MODNUM;
        pearls.push(p);
    }
    
    std::cout << total << std::endl;
    
    
}

