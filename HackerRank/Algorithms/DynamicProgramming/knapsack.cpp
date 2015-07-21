// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>

using std::unordered_set;
using std::vector;

class KnapSack {
public:
    KnapSack();
    int solveKnapSack();
private:
    void readInput();
    unordered_set<int> vals;
    int n;
    int capacity;
};

KnapSack::KnapSack() 
: vals(), n(0), capacity(0) {
    readInput();
}

void KnapSack::readInput() {
    std::cin >> n >> capacity;
    for (int i=0; i<n; i++) {
        int num; std::cin >> num;
        vals.insert(num);
    }
}

int KnapSack::solveKnapSack() {
    vector<bool> sat(capacity+1, false);

    //possible to construct 0 capacity by taking nothing
    sat[0] = true;

    for (int i=1; i<=capacity; i++) {
        for (const int& item : vals) {
            if ((item <= i) && sat[i-item]){
                sat[i] = true;
                break;
            }
        }
    }
    for (int i=capacity; i>=0; i--) {
        if (sat[i]) return i;
    }
    return 0;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        KnapSack ks;
        int ans = ks.solveKnapSack();
        std::cout << ans << std::endl;
    }
}

