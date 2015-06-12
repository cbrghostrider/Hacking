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
#include <vector>
using std::vector;

class QuickSelect {
private:
    vector<int> nums;
    void readInput();
    int partition(int start, int end, int kth);
public:
    QuickSelect();
    int select(int k);
    int selectMid();
};

QuickSelect::QuickSelect()
: nums() {
    readInput();
}

void QuickSelect::readInput() {
    int n, k;
    std::cin >> n;
    for (int i=0; i<n; i++) {
        std::cin >> k;
        nums.push_back(k);
    }
}

int QuickSelect::partition(int start, int end, int kth) {
    if (end == start) return nums[start];
    int& pivot = nums[end];
    int copyto=start;
    for (int examine=start; examine<end; examine++) {
        if (nums[examine] < pivot) {
            std::swap(nums[examine], nums[copyto++]);
        }
    }
    std::swap(pivot, nums[copyto]);
    
    if (copyto == kth) return nums[copyto];
    if (copyto > kth) return partition(start, copyto-1, kth);
    return partition(copyto+1, end, kth);
}

int QuickSelect::select(int kth) {
    if (nums.size() == 0 || kth >= nums.size() || kth < 0) return -1; //illegal
    return partition(0, nums.size()-1, kth);
}

int QuickSelect::selectMid() {
    return select(nums.size()/2);
}
int main() {
    QuickSelect qs;
    int val = qs.selectMid();
    std::cout << val << std::endl;
}
