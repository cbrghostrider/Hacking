// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//
// Current implementation is O(n) time and O(n) space
//
// Note: This can also be done in O(1) space by first computing the total sum
// then keeping track of the running sum and checking difference of that with 
// current element and total sum
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using std::vector;
typedef long long Elem;

class SymmetricSum {
public:
    SymmetricSum();
    bool hasSymmetricSum();
private:
    void readInput();
    void computeCumuSums();
    vector<Elem> nums;  //numbers
    vector<Elem> lcsum; //left cumulative sum
    vector<Elem> rcsum; //right cumulative sum
};

SymmetricSum::SymmetricSum() 
: nums(), lcsum(), rcsum() {
    readInput();
    computeCumuSums();
}

void SymmetricSum::readInput(){
    int n; std::cin >> n;
    for(int i=0; i<n; i++) {
        Elem num; std::cin >> num;
        nums.push_back(num);
    }
}

void SymmetricSum::computeCumuSums(){
    Elem cumusum = 0;
    for (int i=0; i<nums.size(); i++) {
        cumusum += nums[i];
        lcsum.push_back(cumusum);
    }
    cumusum = 0;
    for (int i=nums.size()-1; i>=0; i--) {
        cumusum += nums[i];
        rcsum.push_back(cumusum);
    }
    std::reverse(rcsum.begin(), rcsum.end());
}

bool SymmetricSum::hasSymmetricSum() {
    for (int i=0; i<nums.size(); i++) {
        Elem cleft  = (i == 0) ? 0 : lcsum[i-1];
        Elem cright = (i == nums.size() - 1) ? 0 : rcsum[i+1];
        if (cleft == cright) return true;
    }
    return false;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        SymmetricSum ss;
        bool ans = ss.hasSymmetricSum();
        std::cout << ((ans) ? "YES" : "NO") << std::endl;
    }
}
