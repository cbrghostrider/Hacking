// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>

using std::vector;

unsigned int getUnique(const vector<unsigned int>& nums) {
    unsigned int acc=0;
    for (int i=0; i<nums.size(); i++) {
        acc = acc ^ nums[i];
    }
    return acc;
}

int main() {
    int n;
    std::cin >> n;
    vector<unsigned int> nums;
    for (int i=0; i<n; i++) {
        unsigned int num; std::cin >> num;
        nums.push_back(num);
    }
    std::cout << getUnique(nums) << std::endl;
}

