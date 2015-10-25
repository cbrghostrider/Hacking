// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        long long n, k; std::cin >> n >> k;
        long long sn = (n)*(n+1)/2;

        if (k > sn) {
            std::cout << "NO" << std::endl;
        } else if (k < (2 - sn)) {
            std::cout << "NO" << std::endl;
        } else if ((sn - k) % 2) {
            std::cout << "NO" << std::endl;
        } else {
            std::cout << "YES" << std::endl;
        }
    }
}
