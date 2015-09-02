// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;

int count(int N, int K) {
    int num;
    unordered_set<int> nums;
    for (int i=0; i<N; i++) {
        std::cin >> num; nums.insert(num);
    }
    int count = 0;
    for (const int& n : nums) {
        int diff = K + n;
        auto it = nums.find(diff);
        if (diff > n && it != nums.end()) {
            count++;
        }
    }
    return count;
}

int main() {
    int N, K; std::cin >> N >> K;
    int ans = count(N, K);
    std::cout << ans << std::endl;
}

