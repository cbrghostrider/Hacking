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

unsigned int solveProblem(vector<unsigned int>& nums) {
    //problem reduces to these rules
    //for even sized array, the various xors cancel out perfectly
    if ((nums.size() % 2) == 0) return 0;
    //for odd size arrays, only the consecutive indices remain
    unsigned int result=0;
    for (int i=0; i<nums.size(); i+=2) {
        result ^= nums[i];
    }
    return result;
}

int main() {
    unsigned int tc, n;
    std::cin >> tc;
    for (int i=0; i<tc; i++) {
        std::cin >> n;
        vector<unsigned int> nums;
        for (int k=0; k<n; k++) {
            unsigned int num;
            std::cin >> num;
            nums.push_back(num);
        }
        unsigned int value = solveProblem(nums);
        std::cout << value << std::endl;
    }
}
