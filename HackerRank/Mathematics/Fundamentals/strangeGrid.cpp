// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>

int main() {
    unsigned long long r, c;
    std::cin >> r >> c;

    unsigned long long coffset = ((c-1) * 2) + ((r-1)%2);
    unsigned long long roffset = ((r-1) / 2)*10;
    std::cout << (roffset+coffset) << std::endl;
}
