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

class CountingSort {
private:
    const int NLOW;
    const int NHIGH;
    vector<int> nums;
    vector<int> counts;
    void readInput();
    void printOutput();
    void printArray();
public:
    CountingSort();
    ~CountingSort();
    void sort();    
};

CountingSort::CountingSort() 
: NLOW(0), NHIGH(99), nums(), counts(NHIGH-NLOW+1, 0) {
    readInput();
}

CountingSort::~CountingSort() {
}

void CountingSort::readInput() {
    int n, k;
    std::cin >> n;
    for (int i=0; i<n; i++) {
        std::cin >> k;
        nums.push_back(k);
    }
}

void CountingSort::printArray() {
    for (const int& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

void CountingSort::sort() {
    for (const int& n : nums) {
        counts[n-NLOW]++;
    }
    printOutput();
}

void CountingSort::printOutput() {
    for (int i=0; i<counts.size();i++) {
        for (int j=0; j<counts[i]; j++) {
            std::cout << i << " ";    
        }
    }
    std::cout << std::endl;
}

int main() {
    CountingSort cs;
    cs.sort();
    return 0;
}


