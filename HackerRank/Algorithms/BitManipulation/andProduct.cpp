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

unsigned int andProduct(unsigned int a, unsigned int b) {
    unsigned int mask = 0x1 << 31;
    unsigned int result = 0;
    
    //find highest bit set in bigger number
    while (mask != 0) {
        if (mask & b) break;
        mask >>= 1;
    }
    
    //while these bits exists similarly in both, just accumulate into result
    while (mask && ((mask & a) == (mask & b)) ) {
        result |= (mask & a);
        mask >>= 1;
    }
    
    return result;
}

int main() {
    unsigned int tc, a, b; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        std::cin >> a >> b;
        std::cout << andProduct(a, b) << std::endl;
    }
}
