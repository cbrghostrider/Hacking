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
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        int a, b; std::cin >> a >> b;
        if (a == 0 || b == 0) {
            std::cout << "First" << std::endl; 
            continue;
        }
        if ((a+b)%2) {
            std::cout << "First" << std::endl;
        } else {
            std::cout << "Second" << std::endl; 
        }
    }
}

