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
        int n; 
        unsigned int k; 
        std::cin >> n >> k;
        vector<unsigned int> ns(n, 0);
        for (int ni=0; ni<n; ni++) {
            ns[ni] = ni + 1;
        }
        
        unsigned int a=0, b=0;
        unsigned int val = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (i == j) continue;
                unsigned int newval = ns[i] & ns[j];
                if (newval >= val && newval < k) {
                    val = newval; 
                    a = ns[i];
                    b = ns[j];
                }
            }
        }
        
        std::cout << val << std::endl;
    }
}

