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

class QuickSort {
private:
    vector<int> nums;
    void readInput();
    void printArray();
    void sort(int start, int end);
    int partition(int start, int end);
public:
    QuickSort();
    void sort();
    ~QuickSort();
};

QuickSort::QuickSort()
: nums() {
    readInput();
}

QuickSort::~QuickSort() {

}
void QuickSort::readInput() {
    int n, k;
    std::cin >> n;
    for (int i=0; i<n; i++) {
        std::cin >> k;
        nums.push_back(k);
    }
}

void QuickSort::printArray() {
    for (const int& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int QuickSort::partition(int start, int end) {
    int& pivot = nums[end];
    int copyto=start;
    for (int examine=start; examine<end; examine++) {
        if (nums[examine] < pivot) {
            std::swap(nums[examine], nums[copyto++]);
        }
    }
    std::swap(pivot, nums[copyto]);
    printArray();
    return copyto;
}

void QuickSort::sort(int start, int end) {
    if (start == end) return;
    int ind = partition(start, end);
    if (ind != start) sort(start, ind-1);
    if (ind != end)   sort(ind+1, end);
}

void QuickSort::sort() {
    if (nums.size() == 0) return;
    sort(0, nums.size()-1);
}

int main() {
    QuickSort qs;
    qs.sort();
}
