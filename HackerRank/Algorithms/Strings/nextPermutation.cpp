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
using namespace std;


string next_permutation_str(const string& str) {
    if (str.length() <= 1) return str; //no next permutation possible
    
    int L = str.length();
    int pivot;
    

    for (pivot = 1; pivot < L; pivot++) {
        if (str[pivot] < str[pivot-1]) {
            break;
        }
    }
    if (pivot == L) {return str;} //no rollover to smallest 
    
    string ret = str;
    for (int i=0; i<pivot; i++) {
        if (ret[i] > ret[pivot]) {
            std::swap(ret[i], ret[pivot]);
            break;
        }
    }
    std::sort(ret.begin(), ret.begin() + pivot, std::greater<char>());
    
    return ret;
}

int main() {
    int tc; std::cin >> tc;
    for (int t=0; t<tc; t++) {
        string str; std::cin >> str;
        std::reverse(str.begin(), str.end());
        
        string strn = next_permutation_str(str);
        std::reverse(str.begin(), str.end());
        std::reverse(strn.begin(), strn.end());
        
        if (str != strn) {
            std::cout << strn << std::endl;
        } else {
            std::cout << "no answer" << std::endl;
        }
    }
}

