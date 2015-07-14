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

#define MODNUM (1000000000)

class PascalsTriangle {
private:
    vector<vector<unsigned long long>> pt;
public:
    PascalsTriangle(int n);
    unsigned long long choose(int n, int k);
};

PascalsTriangle::PascalsTriangle(int n) 
: pt(vector<vector<unsigned long long>>(n+1, vector<unsigned long long>(n+1, 1))) { //init [n+1][n+1] matrix to 1s
    for (int row=2; row<=n; row++) {
        for (int col=1; col<row; col++) {
            pt[row][col] = pt[row-1][col-1] + pt[row-1][col];
            pt[row][col] %= (unsigned long long) MODNUM;
        }
    }
}

unsigned long long PascalsTriangle::choose(int n, int k) {
    if (n <= k || k == 0) return 1;
    return pt[n][k];
}

int main() {
    PascalsTriangle pt(1000);
    int tc; std::cin >> tc;
    
    for (int i=0; i<tc; i++) {
        int n; std::cin >> n;
        for (int k=0; k<=n; k++) {
            std::cout << pt.choose(n, k) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

