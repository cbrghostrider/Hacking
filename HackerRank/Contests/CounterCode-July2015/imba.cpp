// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(n) solution for each test
//
#include <iostream>
#include <cstdio>
#include <vector>

using std::vector;

void placeNumbers(int N) {
    vector<int> places(N, 0);
    int lnum=1, rnum=N;
    for (int ptr=N-1; ptr>=0;) {
        places[ptr] = rnum--;
        ptr--;

        if (ptr <0) break;
        
        places[ptr] = lnum++;
        ptr--;
    }
    for (int i=0; i<N; i++) {
        std::cout << places[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        int n; std::cin >> n;
        placeNumbers(n);
    }
}

