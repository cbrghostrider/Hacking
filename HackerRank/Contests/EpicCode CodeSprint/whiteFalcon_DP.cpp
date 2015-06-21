// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------

// currently timing out on big tests (> 1 sec)
// O(n^3) algorithm, could optimize further perhaps!

#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>

using std::vector;

typedef long long NumType;

class WhiteFalcon {
private:
    vector<NumType> nums;
    void readInput(int n);
    bool overlap(int sz, int xi, int yi);
public:
    NumType maxSum();
    WhiteFalcon(int n);
};

WhiteFalcon::WhiteFalcon(int n) 
: nums(n, 0) {
    readInput(n);
}

void WhiteFalcon::readInput(int n) {
    NumType num;
    for (int i=0; i<n; i++) {
        std::cin >> num;
        nums[i] = num;
    }
}

bool WhiteFalcon::overlap(int sz, int xi, int yi) {
    if (xi < yi) {
        return ((xi + sz - 1) >= yi);
    }
    if (yi < xi) {
        return ((yi + sz - 1) >= xi);
    }
    return true;
}

NumType WhiteFalcon::maxSum() {
    NumType maxval=std::numeric_limits<NumType>::min();
    vector<vector<NumType>> cache[2];

    cache[0] = vector<vector<NumType>>(nums.size(), vector<NumType>(nums.size(), 0));
    cache[1] = vector<vector<NumType>>(nums.size(), vector<NumType>(nums.size(), 0));
    int prev=0, next=1;

    //compute the prev cache for base case (sz == 1)
    for (int xi=0; xi<nums.size(); xi++) {
        for (int yi=0; yi<nums.size(); yi++) {
            if (xi == yi) {
                cache[prev][xi][yi] = std::numeric_limits<NumType>::min();
            } else {
                cache[prev][xi][yi] = nums[xi] * nums[yi];
                if (cache[prev][xi][yi] > maxval) {
                    maxval = cache[prev][xi][yi];
                }
            }
        }
    }

    int szlimit = nums.size() / 2;
    //main dynamic programming algorithm  
    for (int sz=2; sz<=szlimit; sz++) {                         //size of contiguous subarrays
        for (int xi=0; xi<(nums.size() - (sz-1)); xi++) {       //x array starts at xi
            for (int yi=0; yi<(nums.size() - (sz-1)); yi++) {   //y array starts at yi
                if (overlap(sz, xi, yi)) { //overlapping sequences not allowed
                    cache[next][xi][yi] = std::numeric_limits<NumType>::min();
                    continue;
                }

                NumType prevProd = cache[prev][xi][yi+1];
                NumType newProd  = prevProd + nums[xi+sz-1] * nums[yi];

                cache[next][xi][yi] = newProd;
                if (newProd > maxval) {
                    maxval = newProd;
                }
            }
        }
        prev = 1-prev;
        next = 1-next;
    }

    return maxval;
}

int main() {
    int n;
    std::cin >> n;
    WhiteFalcon wf(n);
    NumType maxSum = wf.maxSum();
    std::cout << maxSum << std::endl;
}


