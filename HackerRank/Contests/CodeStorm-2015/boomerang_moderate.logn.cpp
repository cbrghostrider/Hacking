// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>

typedef unsigned long long Val;

Val playGame(Val n) {
    const Val step = 4;
    if (n == 2) return 1; 
    if (n == 3) return 2; 
    if (n == 4) return 4; 
    if (n == 5) return 5; 

    Val donen = 5;
    Val size  = 4;

    while ((step*size + donen) < n ) {
        donen += step*size;
        size *= step;
    }

    Val ind = n - donen;
    Val third = (step*size + 2)/3;

    if (ind <= third) {
        return ind;
    }

    Val newind = ind - third;
    Val ret = third + 2;
    ret += ((newind-1)/2) * 3; 
    ret += (newind-1) % 2;
    return ret;
}

int main() {
    int T; std::cin >> T;
    for (int t=0; t<T; t++) {
        Val n; std::cin >> n;
        Val ans = playGame(n);
        std::cout << ans << std::endl;
    }
}

