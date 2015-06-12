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

vector<int> readInput() {
    int n;
    vector<int> nums;
    std::cin >> n;
    for (int k=0, i=0; i<n; i++) {
        std::cin >> k ;
        nums.push_back(k);
    }   
    return nums;
}

int findMinDiff(vector<int>& nums) {
    int minDiff = std::numeric_limits<int>::max();
    for (int i=0; i<nums.size()-1; i++) {
        int diff = abs(nums[i] - nums[i+1]);
        if (diff < minDiff) minDiff = diff;
    }
    return minDiff;
}
                       
int main() {
    vector<int> nums = readInput();
    std::sort(nums.begin(), nums.end());
    int minDiff = findMinDiff(nums);
    for (int i=0; i<nums.size()-1; i++) {
        if (abs(nums[i] - nums[i+1]) == minDiff) {
            std::cout << nums[i] << " " << nums[i+1] << " ";
        }
    }
    std::cout << std::endl;
}

