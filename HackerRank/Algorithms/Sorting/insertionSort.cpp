// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

void printArray(vector<int>& ar) {
    for (const int& n : ar) std::cout << n << " ";
    std::cout << std::endl;
}

//everything to the left of end of pos is sorted
void insertionSort_(vector<int>& ar, int pos) {
    int value = ar[pos];
    for (int i=pos-1; i>=0; i--) {
        if (ar[i]>value) {
            ar[i+1] = ar[i];           
        } else {
            ar[i+1] = value;        
            return;
        }
    }
    ar[0] = value;
}

void insertionSort(vector <int>&  ar) {
    for (int pos=1; pos<ar.size(); pos++) {
        insertionSort_(ar, pos);
        printArray(ar);
    }
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
    insertionSort(_ar);
   
    return 0;
}
