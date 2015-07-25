// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <stdio.h>
#include <map>
#include <vector>
#include <utility>
#include <ostream>
#include <limits>
#include <iostream>

using std::map;
using std::vector;
using std::pair;

typedef unsigned int UInt;

UInt collatz_length (map<UInt, UInt>& m, UInt number)
{
    UInt ret;
    map<UInt, UInt>::iterator it = m.find(number);
    if (it != m.end()) {
        return ((*it).second);
    }
    if (number == 1) {
        ret = 1;
    } else if (number % 2 == 0) {
        ret = (1 + collatz_length(m, number / 2));
    } else {
        ret = (1 + collatz_length(m, 3*number + 1) );
    }
    m.insert(std::pair<UInt, UInt>(number, ret));

    return ret;
}

int main ()
{
    int tc; std::cin >> tc;
    vector<int> nqueries;
    int MAXN = std::numeric_limits<int>::min();
    for (int t=0; t<tc; t++) {
        int n; std::cin >> n;
        nqueries.push_back(n);
        if (n > MAXN) {
            MAXN = n;
        }
    }
    
    map<UInt, UInt> memoized_clength;
    memoized_clength.insert(std::pair<UInt, UInt>(1, 1));
    vector<UInt> clengths;

    clengths.push_back(1); //for 0th entry
    for (UInt i=1; i<=MAXN; i++) {
        clengths.push_back(collatz_length(memoized_clength, i));
    }
    
    for (int t=0; t<tc; t++) {
        int n = nqueries[t];
        UInt maxlen = 1;
        UInt maxnum = 1;       
        for (UInt i=1; i<=n; i++) {
            if (clengths[i] >= maxlen && i > maxnum) {
                maxlen = clengths[i];
                maxnum = i;
            }
        }
        std::cout << maxnum << std::endl;
    }  
}
