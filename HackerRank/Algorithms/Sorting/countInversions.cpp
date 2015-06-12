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
#include <utility>
using namespace std;

void readInput(vector<int>& nums) {
    int n, k;
    std::cin >> n;
    for (int i=0; i<n; i++) {
        std::cin >> k;
        nums.push_back(k);
    }
}

unsigned long long mergeAndCountInversions(vector<int>& nums, vector<int>& left, vector<int>& right) {
    unsigned long long count = 0; 
    int lptr=0, rptr=0;
    for (int i=0; i<left.size()+right.size(); i++) {
        if (lptr == left.size()) {
            std::copy(right.begin()+rptr, right.end(), nums.begin()+i);
            return count;
        } else if (rptr == right.size()) {
            std::copy(left.begin()+lptr, left.end(), nums.begin()+i);
            return count;
        }
        if (left[lptr] > right[rptr]) {
            count += left.size()-lptr;
            nums[i] = right[rptr++];
        } else {
            nums[i] = left[lptr++];
        }
    }
    return count;
}

unsigned long long msortAndCountInversions(vector<int>& nums) {
    if (nums.size() <= 1) {return 0;}
    if (nums.size() == 2) {
        if (nums[0] > nums[1]) {
            std::swap(nums[0], nums[1]);
            return 1;
        }
        return 0;
    }
    int mid = nums.size()/2;
    vector<int> left, right;
    std::copy(nums.begin(), nums.begin()+mid, back_inserter(left));
    std::copy(nums.begin()+mid, nums.end(), back_inserter(right));
    unsigned long long cntl = msortAndCountInversions(left);
    unsigned long long cntr = msortAndCountInversions(right);
    unsigned long long cntm = mergeAndCountInversions(nums, left, right);
    return (cntl + cntr + cntm);
}

int main() {
    int t;
    std::cin >> t;
    for (int i=0; i<t; i++) {
        vector<int> nums;
        readInput(nums);
        unsigned long long count = msortAndCountInversions(nums);
        std::cout << count << std::endl;
    }
}
