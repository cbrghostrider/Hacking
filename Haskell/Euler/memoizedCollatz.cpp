#include <stdio.h>
#include <map>
#include <vector>
#include <utility>
#include <ostream>
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
    map<UInt, UInt> memoized_clength;
    memoized_clength.insert(std::pair<UInt, UInt>(1, 1));
    vector<UInt> clengths;
    UInt maxlen = 1;
    UInt maxnum = 1;
    clengths.push_back(1); //for 0th entry
    for (UInt i=1; i<1000000; i++) {
        clengths.push_back(collatz_length(memoized_clength, i));
        if (clengths[i] > maxlen) {
            maxlen = clengths[i];
            maxnum = i;
        }
    }
    std::cout << "Collatz length of number " << maxnum << " is " << maxlen << " and is the max." << std::endl;
}
