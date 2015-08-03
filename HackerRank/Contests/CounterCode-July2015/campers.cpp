// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
// 
// O(n) solution
//
#include <iostream>
#include <cstdio>
#include <vector>

using std::vector;

class Campers{
public:
    Campers(int n, int k);
    int maxSet();
private:
    bool shouldMark(int i);
    const int N;
    const int K;
    vector<bool> nums;
};

Campers::Campers(int n, int k)
: N(n), K(k), nums(N, false) {
    int nn;
    for (int i=0; i<K; i++) {
        std::cin >> nn; 
        nn -= 1;
        nums[nn] = true; //chosen
    }
}

bool Campers::shouldMark(int i) {
    return (nums[i] == false && ( (i == nums.size()-1) || nums[i+1] == false) && ((i == 0) || nums[i-1] == false) );
}

int Campers::maxSet() {
    //find first sniper, and scan backwards
    int pos = 0;
    for (int i=0; i<N; i++) {
        if (nums[pos]) {
            break;
        }
    }
    if (K != 0) {
        for (int i=pos; i>=0; i--) {
            if (shouldMark(i)) {
                nums[i] = true;
            }
        }
    }
    for (int i=pos; i<N; i++) {
        if (shouldMark(i)) {
            nums[i] = true;
        }
    }

    int count = 0;
    for (int i=0; i<N; i++) {
        if (nums[i]) {
            count++;
        }
    }
    return count;
}

int main() {
    int n, k; std::cin >> n >> k;
    Campers campers(n, k); 
    int ans = campers.maxSet();
    std::cout << ans << std::endl;
}

