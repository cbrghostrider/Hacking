// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include <algorithm>

typedef unsigned int U32;
typedef int I32;

class CountOnes {
public:
    CountOnes(int a, int b);
    long long countOnes();
private:
    long long countBitPosContribution(U32 bitpos, I32 MA, I32 MB);
    int MB;
    int MA;
};

CountOnes::CountOnes(int a, int b) 
: MA(a), MB(b) {
}

//trailing number is the value from [(bitpos-1)..0] of MA
long long CountOnes::countBitPosContribution(U32 bitpos, I32 MA, I32 MB) {
    long long count = 0;

    //contribution denotes whether this bit is currently a 1 or a 0
    U32 contribution = (((U32)(MA)) & (((U32)1) << bitpos)) ? 1 : 0;

    //these are the total number of values to be considered
    long long totalIters = (long long)MB - (long long)MA + 1;

    //bitpos stays its current value for certain # iters, depending on trailingNumber
    U32 sbitmask   = (((U32)1) << bitpos) - 1;
    I32 trailingNum = MA & sbitmask;
    long long initIters = (((U32)1) << bitpos) - (U32)(trailingNum);
    if (totalIters <= initIters) {
        return (contribution * totalIters);
    }
    count += contribution * initIters;

    //now bit position flips for the first time
    contribution = 1 - contribution;

    //bitpos then flips every certain #iterations
    long long workIters = ((U32)(totalIters - initIters)) / (((U32)1) << bitpos);
    long long usefulIters = workIters / 2 + ((workIters % 2) && (contribution) ? 1 : 0);
    long long onesPerFlip = (((U32)1) << bitpos);
    count += usefulIters * onesPerFlip;

    //if number of flips above was odd, then change bit position contribution value
    if (workIters % 2) {
        contribution = 1 - contribution;
    }

    //finally bitpos stays the final value for certain # iters
    long long finalIters = ((U32)(totalIters - initIters)) % (((U32)1) << bitpos);
    count += finalIters * contribution;

    return count;
}

long long CountOnes::countOnes() {
    long long total = 0;
    for (int bp=0; bp<=31; bp++) {
        long long localCount = countBitPosContribution(bp, MA, MB);
        //std::cout << "Bit " << bp << ": " << localCount << std::endl;
        total += localCount;
    }
    return total;
}

int main() {
    int tc; std::cin >> tc;
    for (int i=0; i<tc; i++) {
        int a, b; std::cin >> a >> b;
        CountOnes co(a, b);
        long long ans = co.countOnes();
        std::cout << ans << std::endl;
    }
}



