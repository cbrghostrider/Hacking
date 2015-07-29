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

void computeResult(vector<int>& vals, int k) {
    std::sort(vals.begin(), vals.end());
    int mindiff = std::numeric_limits<int>::max();
    
    for (int i=k-1; i<vals.size(); i++) {
        int newdiff = vals[i] - vals[i-k+1];
        if (newdiff < mindiff) {
            mindiff = newdiff;
        }
    }
    std::cout << mindiff << std::endl;
}

int main() {
    int n, k; std::cin >> n >> k;
    vector<int> vals; 
    vals.reserve(n);
    for (int i=0; i<n; i++) {
        int num; std::cin >> num;
        vals.push_back(num);
    }
    computeResult(vals, k);
}
