// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;

int main() {
    int T; std::cin >> T;
    for (int t=0; t<T; t++) {
        int N; std::cin >> N;
        vector<bool> cities(N, false);
        for (int i=0; i<N; i++) {
            int val; std::cin >> val;
            if (val) cities[i] = true;
        }
        
        int count=0;
        
        //only 1 city
        if (N == 1) {
            std::cout << 0 << std::endl;
            continue;
        }
        
        for (int i=1; i<N; i++) {
            if (cities[i-1] == true || cities[i] == true) continue;
            cities[i] = true;
            count++;
        }
        std::cout << count << std::endl;
    }
}
