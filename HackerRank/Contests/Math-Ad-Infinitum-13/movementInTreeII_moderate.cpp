// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>

typedef long long Val;
const Val MODNUM = 1000000007;

Val myPow(Val x, Val n) {
    if (n == 0) return 1;
    if (n == 1) return x;
    Val subPow = myPow(x, n/2); //divide and conquer
    Val retval = subPow * subPow  ;
    retval %= MODNUM;
    retval *= (n % 2 == 1 ? x : 1);
    retval %= MODNUM;
    return retval;
}

Val findSeries(Val d, Val k) {
    if (d == 1) return ((k+1) % MODNUM); 
    Val term1 = myPow(d, k+1) + MODNUM - 1;
    term1 %= MODNUM;
    Val term2 = myPow(d - 1, MODNUM - 2);
    Val ans = term1 * term2;
    ans %= MODNUM;
    return ans;
}

Val computeUnr(bool iseven, Val d, Val k, Val h) {
    Val n = (k - h - 1) / 2;
    Val dmult = ((iseven) ? d : 1);
    Val f  = d * d; 
    f %= MODNUM;
    Val ser = findSeries(f, n);
    Val term = dmult * ser;
    term %= MODNUM;
    return term;
}

Val computeUnrEven(Val d, Val k, Val h) {
    return computeUnr(true, d, k, h);
}

Val computeUnrOdd(Val d, Val k, Val h) {
    return computeUnr(false, d, k, h);
}

Val unreacheable(Val d, Val k, Val h) {
    if (h >= k) {
        return 0;
    }
    if (((k - h) % 2) == 0) {
        return computeUnrEven(d, k, h);
    }
    return computeUnrOdd(d, k, h);
}

Val computeAns(Val d, Val k, Val h) {
    Val dt = findSeries(d, k);
    Val delta = unreacheable(d, k, h);
    Val ans = dt - delta + MODNUM;
    ans %= MODNUM;
    return ans;
}

int main() {
    Val tc; std::cin >> tc;
    for (Val t=0; t<tc; t++) {
        Val d, k, h; std::cin >> d >> k >> h;
        Val ans = computeAns(d, k, h);
        std::cout << ans << std::endl;
    }
}

