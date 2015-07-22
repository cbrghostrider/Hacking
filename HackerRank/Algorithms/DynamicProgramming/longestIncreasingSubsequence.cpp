// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using std::vector;
using std::make_pair;
using std::pair;

typedef pair<int, int> Vip; //(length,Previndex)-pair

class LISSequence {
public:
    LISSequence();
    int computeLengthLIS();
private:
    void readInput();
    vector<int> nums;
};

LISSequence::LISSequence() 
: nums() {
    readInput();
}

void LISSequence::readInput() {
    int n; std::cin >> n;
    for (int i=0; i<n; i++) {
        int num; std::cin >> num;
        nums.push_back(num);
    }
}

int LISSequence::computeLengthLIS() {
    vector<Vip> cache(nums.size(), make_pair(0, -1));

    for (int i=0; i<nums.size(); i++) {
        pair<int, int> cand = make_pair(1, -1); //1 long and no prev index i.e. myself only
        for (int j=i-1; j>=0; j--) {
            if (nums[j] < nums[i] && (cache[j].first + 1) > cand.first) {
                cand = make_pair(cache[j].first + 1, j);
            }
        }
        cache[i] = cand;
    }
    int ans = 0;
    for (int i=0; i<cache.size(); i++) {
        if (cache[i].first > ans) ans = cache[i].first;
    }
    return ans;
}

int main() {
    LISSequence lis;
    int ans = lis.computeLengthLIS();
    std::cout << ans << std::endl;
}

