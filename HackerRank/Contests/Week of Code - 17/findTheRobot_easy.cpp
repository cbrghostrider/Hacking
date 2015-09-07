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
    int tc = 0; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        int n; std::cin >> n;
        int mod = n % 4;
        int ndiv4 = n/4;
        int x=0, y=0;
        if (ndiv4) {
            x -= 2 * ndiv4;
            y -= 2 * ndiv4;
        }
        if (mod) { x += ndiv4*4 + 1; mod--;}
        if (mod) { y += ndiv4*4 + 2; mod--;}
        if (mod) { x -= ndiv4*4 + 3; }
        std::cout << x << " " << y << std::endl;
    }
}

