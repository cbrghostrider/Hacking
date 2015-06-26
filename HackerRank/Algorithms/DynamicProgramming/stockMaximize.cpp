// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// Simple recursion problem, not DP
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

// last day is max price for [from, to] interval
// so buy everyday except last, when you dump all
long long maxStockGainPrime(vector<long long>& sv, int from, int to) {
    if ((to-from+1) <= 1) return 0;

    long long money_spent = 0;

    for (int si=from; si<to; si++) {
        money_spent += sv[si];
    }

    long long money_recv  = (to-from) * sv[to];

    return (money_recv - money_spent);
}

long long maxStockGain(vector<long long>& sv, int from, int to) {
    if (from > to) return 0;

    int maxind = from;
    for (int i=from; i<=to; i++) {
        if (sv[i] >= sv[maxind]) {
            maxind = i;
        }
    }
    long long lhsPrice  = maxStockGainPrime(sv, from, maxind);
    long long restPrice = maxStockGain(sv, maxind+1, to);

    return(lhsPrice + restPrice);
}


int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        int n; std::cin >> n;
        vector<long long> stock;
        for (int i=0; i<n; i++) {
            long long sv;
            std::cin >> sv;
            stock.push_back(sv);
        }
        long long ans = maxStockGain(stock, 0, stock.size()-1);
        std::cout << ans << std::endl;
    }

}

