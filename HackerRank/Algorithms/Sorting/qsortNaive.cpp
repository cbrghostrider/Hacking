// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void printArray(vector<int>& nums) {
    for (const int& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

void partition(vector <int>& ar) {
    if (ar.size() <= 1) return;
    int start = 0, end = ar.size()-1;
    int pivot = ar[start];
    
    vector<int> smaller, larger;
    for (int i=1; i<ar.size(); i++) {
        if (ar[i] <= pivot) smaller.push_back(ar[i]);
        else larger.push_back(ar[i]);
    }
    partition(smaller);
    partition(larger);
    int arctr=start;
    for (int& n : smaller) ar[arctr++] = n;
    ar[arctr++] = pivot;
    for (int& n : larger) ar[arctr++] = n;
    printArray(ar);
}

void quickSort(vector <int> &arr) {
   partition(arr);
}

int main() {
    int n;
    scanf("%d", &n);

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr);

    return 0;
}
