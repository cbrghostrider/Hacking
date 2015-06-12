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

using std::vector;

class BinSearch {
private:
    vector<int> nums;
    int binarySearch(int lo, int hi, int val);
public:
    BinSearch(int n);
    int findNum(int v);
};

//reads in already sorted numbers
BinSearch::BinSearch(int n) {
    for (int i=0; i<n; i++) {
        int k;
        std::cin >> k;
        nums.push_back(k);
    }
}
int BinSearch::binarySearch(int lo, int hi, int val) {
    if (lo == hi) {
        if (nums[lo] == val) return lo;
        return -1;
    }
    if (lo + 1 == hi) {
        if (nums[lo] == val) return lo;
        if (nums[hi] == val) return hi;
        return -1; 
    }
    int mid     = (hi+lo)/2;
    int midplus = mid+1;

    if (nums[mid] < val && nums[midplus] > val) return -1;
    if (nums[mid] >= val) return binarySearch(lo, mid, val);
    return binarySearch(midplus, hi, val);
}

int BinSearch::findNum(int value) {
    if (nums.size() == 0) return -1;
    return binarySearch(0, nums.size()-1, value);
}

int main() {
    int v, n;
    std::cin >> v >> n;
    BinSearch bs(n);

    int ans = bs.findNum(v);
    std::cout << ans << std::endl;

    return 0;
}
