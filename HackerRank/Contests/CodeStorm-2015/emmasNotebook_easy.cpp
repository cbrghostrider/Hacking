// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>

int main(){
    int t;
    std::cin >> t;
    long long ones = 0;
    for (int i=1; i<=t; i++) {
        if ((i % 2) == 0) { //even secs
            ones += i/2 + 1;
        } else { //odd secs
            ones += (i+1)/2;
        }
    }
    std::cout << ones << std::endl;
    return 0;
}
