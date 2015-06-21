// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <unordered_map>
#include <string>

using std::string;
using std::unordered_map;

typedef unordered_map<char, unsigned long long> HTable;

class BeginEnd {
private:
    string s;
    unsigned long long sumFirstK(unsigned long long k);
public:
    BeginEnd();
    void readInput();
    unsigned long long beginEnd();
};

BeginEnd::BeginEnd() 
: s() {
}

void BeginEnd::readInput() {
    std::cin >> s;
}

unsigned long long BeginEnd::sumFirstK(unsigned long long k) {
    return ((k * (k+1))/2);
}

unsigned long long BeginEnd::beginEnd() {
    HTable table;
    for (int i=0; i<s.length(); i++) {
        if (table.find(s[i]) == table.end()) {
            table[s[i]] = 1;
        } else {
            table[s[i]] += 1;
        }
    }
    unsigned long long retval = 0;
    for (auto cvp : table) {
        retval += sumFirstK(cvp.second);
    }
    return retval;
}


int main()
{
    int junk;std::cin >> junk;

    BeginEnd be;
    be.readInput();

    unsigned long long ans = be.beginEnd();
    std::cout << ans << std::endl;
}


