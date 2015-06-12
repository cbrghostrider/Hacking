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

void readInput(vector<int>& nums, int& k, int& q) {
    int n, rn;
    std::cin >> n >> k >> q;
    for (int i=0; i<n; i++) {
        std::cin >> rn;
        nums.push_back(rn);
    }
}

int main() {
    vector<int> nums;
    int k=0, q=0;
    readInput(nums, k, q);
    if (k < 0) return 0; //illegal
    
    k %= nums.size();
    std::rotate(nums.begin(), nums.begin()+nums.size()-k, nums.end());
    
    for (int qi=0; qi<q; qi++) {
        int idx;
        std::cin >> idx;
        std::cout << nums[idx] << std::endl;
    }
}
