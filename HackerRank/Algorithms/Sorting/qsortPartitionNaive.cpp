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

void partition(vector <int>&  ar) {
    int start=0, end = ar.size()-1;
    int pivot = ar[start];
    vector<int> smaller, larger;
    for (int i=1; i<ar.size(); i++) {
        if (ar[i] <= pivot) smaller.push_back(ar[i]);
        else larger.push_back(ar[i]);
    }
    ar.clear();
    ar = smaller;
    ar.push_back(pivot);
    ar.insert(ar.end(), larger.begin(), larger.end());
    printArray(ar);
}
int main(void) {
    vector <int>  _ar;
    int _ar_size;
    cin >> _ar_size;
    for(int _ar_i=0; _ar_i<_ar_size; _ar_i++) {
       int _ar_tmp;
       cin >> _ar_tmp;
       _ar.push_back(_ar_tmp); 
    }

    partition(_ar);
   
    return 0;
}

