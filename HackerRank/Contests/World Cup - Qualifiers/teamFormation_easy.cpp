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

const int NUM = 10;

int main() {
    vector<int> rating;
    for (int i=0; i<NUM; i++) {
        int num; std::cin >> num;
        rating.push_back(num);
    }
    std::sort(rating.begin(), rating.end(), std::greater<int>());
    int score = 0;
    for (int i=0; i<3*2; i++) {
        if ((i%2) == 0) score += rating[i];
    }
    std::cout << score << std::endl;
}

