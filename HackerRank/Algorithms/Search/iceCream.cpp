// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// used nested for, instead of two-sum using hash table... yawn...
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;

void processTwoSum() {
    vector<int> prices;
    int m, n; std::cin >> m ; std::cin >> n;
    for (int i=0; i<n; i++) {
        int price; std::cin >> price;
        prices.push_back(price);
    }
    for (int i=0; i<prices.size(); i++) {
        for (int j=i+1; j<prices.size(); j++) {
            if (prices[i] + prices[j] == m) {
                std::cout << i+1 << " " << j+1 << std::endl;
                return;
            }
        }
    }
}
int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        processTwoSum();
    }
}
