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
typedef unsigned int Elem;

class PickPerms {
public:
    PickPerms(int n, int k);
    bool permsPossible();
private:
    void readInput(vector<Elem>& ss);
    const int N;
    const int K;
    vector<Elem> as;
    vector<Elem> bs;
};

PickPerms::PickPerms(int n, int k)
: N(n), K(k) {
    readInput(as);
    readInput(bs);
}

void PickPerms::readInput(vector<Elem>& ss) {
    ss.reserve(N);
    Elem val;
    for (int i=0; i<N; i++) {
        std::cin >> val;
        ss.push_back(val);
    }
}

bool PickPerms::permsPossible() {
    vector<bool> picked(bs.size(), false); //mark bs that are picked
    
    std::sort(as.begin(), as.end(), std::greater<Elem>()); //sort descending
    std::sort(bs.begin(), bs.end()); //sort ascending
    
    for (int ai=0; ai<as.size(); ai++) { //pick an as to pair
        bool pickedIt = false;
        for (int bi=0; bi<bs.size(); bi++) { //pick a bs to pair with the prior as
            if (picked[bi] == false && (as[ai] >= K || bs[bi] >= K - as[ai])){
                picked[bi] = true;
                pickedIt = true;
                break;
            }
        }
        if (!pickedIt) {
            return false; //found a pairing that could not be done
        }
    }
    return true;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        int n, k; std::cin >> n >> k;
        PickPerms pp(n, k);
        bool ans = pp.permsPossible();
        std::cout << (ans ? "YES" : "NO") << std::endl;
    }
}

