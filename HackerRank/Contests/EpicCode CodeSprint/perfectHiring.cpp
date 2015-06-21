// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;

typedef long long Score;

class PerfectHiring {
private:
    vector<Score> scores;
    Score patience;
    const Score x;

    void readInput(int n);
public:
    PerfectHiring(int n, Score pat, Score xval);
    int perfectHiring();
    ~PerfectHiring() {}
};

PerfectHiring::PerfectHiring(int n, Score pat, Score xval)
: scores(n, 0), patience(pat), x(xval) {
    readInput(n);
}

void PerfectHiring::readInput(int n) {
    Score num;
    for (int i=0; i<n; i++) {
        std::cin >> num;
        scores[i] = num;
    }
}

int PerfectHiring::perfectHiring() {
    Score max=0;
    int chosenid=0;
    for (int id=0; id<scores.size(); id++) {
        Score rating = patience * scores[id];
        if (rating > max) {
            max = rating;
            chosenid = id;
        }
        patience -= x;
    }
    return chosenid + 1;
}

int main() {
    int n;
    Score pat, xval;
    std::cin >> n;
    std::cin >> pat >> xval;

    PerfectHiring ph(n, pat, xval);
    Score ans = ph.perfectHiring();
    std::cout << ans << std::endl;
}
