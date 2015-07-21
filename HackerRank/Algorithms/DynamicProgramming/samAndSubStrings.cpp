// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;

const unsigned long MODNUM = 1000000007;

class SubStringSum {
public:
    SubStringSum();
    unsigned long substringSum();
private:
    void readInput();
    vector<unsigned long> digits;
};

SubStringSum::SubStringSum()
: digits() {
    readInput();
}

void SubStringSum::readInput() {
    string str; std::cin >> str;
    //std::reverse(str.begin(), str.end());

    for (int i=0; i<str.length(); i++) {
        digits.push_back(str[i] - '0');
    }
}

unsigned long SubStringSum::substringSum() {
    vector<unsigned long> cache(digits.size(), 0);
    cache[0] = digits[0];

    for (int i=1; i<digits.size(); i++) {
        cache[i] = cache[i-1] * 10 + (i+1) * digits[i];
        cache[i] %= MODNUM;
    }

    unsigned long total = 0;
    for (const unsigned long& num : cache) {
        total += num;
        total %= MODNUM;
    }
    return total;
}

int main() {
    SubStringSum sss;
    unsigned long ans = sss.substringSum();
    std::cout << ans << std::endl;
}
