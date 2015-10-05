// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string.h>

using std::vector;

class LCS3 {
public:
    LCS3(int n);
    ~LCS3();
    void solve();
private:
    void allocCache();
    void deallocCache();
    void clearCache(int **cache); 
    void readInput();

    const int N;
    int **cacheprev;
    int **cachenext;
    vector<int> A, B, C;
};

LCS3::LCS3(int n) 
: N(n), cacheprev(), cachenext(), A(N+1, 0), B(N+1, 0), C(N+1, 0) {
    allocCache();
    readInput();
}

LCS3::~LCS3() {
    deallocCache();
}


void LCS3::allocCache() {
    cacheprev = new int*[N+1];
    cachenext = new int*[N+1];
    for (int i=0; i<=N; i++) {
        cacheprev[i] = new int[N+1]();
        cachenext[i] = new int[N+1]();
    }
}

void LCS3::deallocCache() {
    for (int i=0; i<=N; i++) {
        delete [] cacheprev[i];
        delete [] cachenext[i];
    }
    delete [] cacheprev;
    delete [] cachenext;
}

void LCS3::readInput() {
    for (int i=1; i<=N; i++) { std::cin >> A[i]; }
    for (int i=1; i<=N; i++) { std::cin >> B[i]; }
    for (int i=1; i<=N; i++) { std::cin >> C[i]; }
}

void LCS3::clearCache(int **cache) {
    for (int i=0; i<=N; i++) {
        memset(cache[i], 0, ((N+1) * sizeof(int)));
    }
}

void LCS3::solve() {
    int maxlen = 0;

    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            for (int k=1; k<=N; k++) {
                if (A[i] == B[j] && B[j] == C[k]) {
                    cachenext[j][k] = 1 + cacheprev[j-1][k-1];
                } else {                    
                    if (cacheprev[j][k] > cachenext[j][k]) cachenext[j][k] = cacheprev[j][k];
                    if (cachenext[j-1][k] > cachenext[j][k]) cachenext[j][k] = cachenext[j-1][k];
                    if (cachenext[j][k-1] > cachenext[j][k]) cachenext[j][k] = cachenext[j][k-1];
                    if (cacheprev[j-1][k] > cachenext[j][k]) cachenext[j][k] = cacheprev[j-1][k];
                    if (cacheprev[j-1][k] > cachenext[j][k]) cachenext[j][k] = cacheprev[j-1][k];
                    if (cachenext[j-1][k-1] > cachenext[j][k]) cachenext[j][k] = cachenext[j-1][k-1];
                    if (cacheprev[j-1][k-1] > cachenext[j][k]) cachenext[j][k] = cacheprev[j-1][k-1];
                    
                    if (cachenext[j][k] > maxlen) { maxlen = cachenext[j][k]; }
                }
            }
        }
        int **temp = cacheprev;
        cacheprev = cachenext;
        cachenext = temp;
        //clearCache(cachenext);
    }
    std::cout << maxlen << std::endl;
}

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        int n; std::cin >> n;
        LCS3 lcs(n);
        lcs.solve();
    }
}

