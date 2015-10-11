// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

using std::string;
using std::vector;

const int N = 5000000;

class MagicalString {
public:
    MagicalString();
    void runQueries();
private:
    int runSingleQuery();
    void populateMagical();
    void populatePreComps();  
    string magical;
    vector<int> ones;
    vector<int> twos;
};

MagicalString::MagicalString() 
: magical(),
  ones(N, 0),
  twos(N, 0) {
}

void MagicalString::populateMagical() {
    magical = string("1221121221221121122");
    int genindex   = magical.size(); //next place to write
    int checkindex = 12;             //next place to check
    char writeme   = '1';            //next character to write

    while (genindex < N) {
        int num = (magical[checkindex] == '1') ? 1 : 2; //put these many writeme characters next
        for (int i=0; i<num; i++) {
            magical.push_back(writeme);
        }
        writeme = ((writeme == '1') ? '2' : '1');
        genindex += num;
        checkindex++;
    }
}

void MagicalString::populatePreComps() {
    int countOnes=0, countTwos=0;
    for (int i=0; i<N; i++) {
        if (magical[i] == '1') {
            countOnes++;
        } else {
            countTwos++;
        }
        ones[i] = countOnes;
        twos[i] = countTwos;
    }
}

int MagicalString::runSingleQuery() {
    int type, n; std::cin >> type >> n;
    n -= 1; //make 0-indexed

    if (type == 1) {
        return ones[n];
    } else {
        return twos[n];
    }
}

void MagicalString::runQueries() {
    int Q; std::cin >> Q;

    populateMagical();
    populatePreComps();

    for (int q=0; q<Q; q++) {
        int ans = runSingleQuery();
        std::cout << ans << std::endl;
    }
}

int main() {
    MagicalString ms;
    ms.runQueries();
}


