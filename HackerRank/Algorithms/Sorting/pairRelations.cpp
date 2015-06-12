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
#include <utility>
#include <limits>

using std::vector;
using std::pair;
using std::make_pair;

class PairRelations {
private:
    vector<int> nums;
    vector<pair<int, int>> numInds; //(number, index-of-number)
    void compileNumIndices();
    void readInput();
public:
    PairRelations();
    ~PairRelations() {}
    unsigned long long countPairRelations();
};

void PairRelations::readInput() {
    int n, k;
    std::cin >> n;
    for (int i=0; i<n; i++) {
        std::cin >> k;
        nums.push_back(k);
    }
}

PairRelations::PairRelations() 
: nums() {
    readInput();
}

void PairRelations::compileNumIndices() {
    for (int i=0; i<nums.size(); i++) {
        numInds.push_back(make_pair(nums[i], i));
    }
}

unsigned long long PairRelations::countPairRelations() {
    compileNumIndices();
    
    //sort on numbers
    std::sort(numInds.begin(), numInds.end(), [] (const pair<int, int>& lhs, const pair<int, int>& rhs) -> bool {
        return (lhs.first < rhs.first);
    });
    
    unsigned long long ans=0;
    
    auto it=numInds.begin();
    while (it != numInds.end()) {
        int value = it->first;
        vector<pair<int, int>>::iterator eit = std::find_if_not(it, numInds.end(), [value] (const pair<int, int>& e1) -> bool {
            return (e1.first == value);
        });
        unsigned long long count = std::count_if(it, eit, [value] (const pair<int, int>& e) -> bool {
            return (e.first == value);
        });
        unsigned long long check = std::numeric_limits<unsigned int>::max();
        if (count >= 2) {
            ans += (count * (count-1));
        }
        it = eit;
    }
    
    return ans;
}

int main() {
    int t;
    std::cin >> t;
    for (int i=0; i<t; i++) {
        PairRelations pr;
        unsigned long long ans = pr.countPairRelations();
        std::cout << ans << std::endl;
    }

    return 0;
}


