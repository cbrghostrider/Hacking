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

using std::vector;

unsigned long highestBit(unsigned long k) {
    unsigned long mask = ((unsigned long)0x1) << 63;
    while (mask) {
        if (mask & k) break;
        mask >>= 1;
    }
    return mask;
}

unsigned long playGame(unsigned long n) {
    unsigned long turns=0;
    
    while (n != 1) {
        if (n == 0) { turns++; break; }
        unsigned long highBit = highestBit(n);
        if ((highBit & n) == n) { //power of 2
            n >>= 1;
        } else {
            //n -= highBit;
            n &= (~highBit);
        }
        turns++;
    }
    return turns;
}

int main() {
    unsigned long n, tc; std::cin >> tc;
    for (unsigned long i=0; i<tc; i++) {
        std::cin >> n;
        if (playGame(n) % 2) {
            std::cout << "Louise" << std::endl;
        } else {
            std::cout << "Richard" << std::endl;            
        }
    }
}

