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


int main() {
    long long N, T;
    std::cin >> N >> T;
    
    long long mult = N / 4;
    long long delta = mult * 2;
    long long rem = N % 4;
    
    long long newtime = mult * 2 + 1;
    
    if (rem) {delta -= newtime; rem--;}
    if (rem) {delta -= newtime; rem--; newtime++;}
    if (rem) {delta += newtime; rem--;}
    
    long long ans = T + delta;
    
    std::cout << ans << std::endl;
    
}

