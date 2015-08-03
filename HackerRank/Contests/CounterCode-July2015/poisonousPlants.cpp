// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(n^2) too slow for 3 tests
//
#include <vector>
#include <iostream>
#include <cstdio>

using std::vector;

class PoisonousPlants {
public:
    PoisonousPlants(int n);
    int simResult();
private:
    int N;
    vector<int> plants;
    vector<bool> alive;
};

PoisonousPlants::PoisonousPlants(int n)
: N(n), plants(N, 0), alive(N, true) {
    for (int i=0; i<N; i++) {
        std::cin >> plants[i];
    }
}

int PoisonousPlants::simResult() {
    int iters=0;
    bool change = true;
    while (change) {
        change = false;
        int ptr=0;
        int prev=-1;
        for (ptr=0; ptr<N; ptr++) {
            if (alive[ptr]) {
                prev = plants[ptr];
                break;
            }
        }
        if (prev == -1) break;
        for (ptr = ptr+1; ptr<N; ptr++) {
            if(alive[ptr]) {
                if (plants[ptr] > prev) {
                    alive[ptr] = false;
                    change = true;
                }
                prev = plants[ptr];
            }
        }
        if (change) iters++;
    }
    return iters;
}

int main() {
    int n; std::cin >> n;
    PoisonousPlants pp(n);
    int ans = pp.simResult();
    std::cout << ans << std::endl;
}


