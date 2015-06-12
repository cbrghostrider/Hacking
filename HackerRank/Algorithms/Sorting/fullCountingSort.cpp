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
#include <string>
#include <utility>
using namespace std;

class CountingSort {
private:
    const int NLOW;
    const int NHIGH;
    vector<pair<int, string> > items;
    vector<vector<string> > counts;
    void readInput(bool twist);
    void printOutput();
    void printArray();
public:
    CountingSort();
    ~CountingSort();
    void sort();    
};

CountingSort::CountingSort() 
: NLOW(0), NHIGH(99), items(), counts(NHIGH-NLOW+1, vector<string>()) {
    readInput(true);
}

CountingSort::~CountingSort() {
}

void CountingSort::readInput(bool twist) {
    int n, k;
    string somestr;
    std::cin >> n;
    for (int i=0; i<n; i++) {
        std::cin >> k >> somestr;
        if (twist && i<n/2) somestr = "-";
        items.push_back(make_pair(k, somestr));
    }
}

void CountingSort::printArray() {
    for (auto ns : items) {
        std::cout << ns.first << " " << ns.second << std::endl;;
    }
    std::cout << std::endl;
}

void CountingSort::sort() {
    for (auto ns : items) {
        counts[ns.first-NLOW].push_back(ns.second);
    }
    printOutput();
}

void CountingSort::printOutput() {
    for (int i=0; i<counts.size();i++) {
        for (const string& str : counts[i]) {
            std::cout << str << " "; 
        }
    }
    std::cout << std::endl;
}

int main() {
    CountingSort cs;
    cs.sort();
    return 0;
}


