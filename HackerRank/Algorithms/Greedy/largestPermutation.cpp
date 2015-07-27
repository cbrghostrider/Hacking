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

class LargestPermutation {
public:
    LargestPermutation(int n, int k);
    void showLargestPerm();
private:
    void readInput();
    const int N; 
    const int K;
    vector<int> ns;
};

LargestPermutation::LargestPermutation(int n, int k)
: N(n), K(k) {
    readInput();        
}

void LargestPermutation::readInput() {
    ns.reserve(N);
    int val;
    for (int i=0; i<N; i++) {
        std::cin >> val;
        ns.push_back(val);
    }
}

void LargestPermutation::showLargestPerm() {
    int val = N; //largest number to start with
    for (int i=0, swaps=0; i<ns.size() && swaps < K; i++) {
        if (ns[i] != val) {
            for (int j=i+1; j<ns.size(); j++) {
                if (ns[j] == val) {
                    std::swap(ns[i], ns[j]);
                    swaps++;
                    break;
                }
            }
        }
        val--;
    }
    
    for (int i=0; i<ns.size(); i++) {
        std::cout << ns[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n, k; std::cin >> n >> k;
    LargestPermutation lp(n, k);
    lp.showLargestPerm();
}

