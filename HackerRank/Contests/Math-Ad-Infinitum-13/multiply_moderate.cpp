// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <utility>

using std::unordered_map;
using std::pair;
using std::make_pair;
using std::vector;

typedef unsigned long long Val;

#define NUMLIMIT (1000050)
#define MODNUM (1000000007)

unordered_map<Val, Val> primePowCache;

std::vector<Val> primes ;

inline Val makeKey(Val prime, Val exp) {
    return ((prime << 32) | (exp));
}

Val myPow(Val x, Val n) {
    if (n == 0) return 1;
    if (n == 1) return x;
    Val subPow = myPow(x, n/2); //divide and conquer
    Val retval = subPow * subPow;
    retval %= MODNUM;
    retval *= (n % 2 == 1 ? x : 1);
    retval %= MODNUM;
    return retval;
}

void generatePrimes(int n){
    std::vector<bool>sieve(n, true) ;
    for( std::size_t i = 2 ; i < sieve.size() ; ++i ) 
        if( sieve[i] ) {
            primes.push_back(i);
            
            //std::cout << "Prime: " << i << std::endl;
            for( std::size_t j = i*2 ; j < sieve.size() ; j += i ) {
                sieve[j] = false ;
            }
        }
}

struct PFactor {
    int prime; 
    int exp;
    PFactor(int p, int e) : prime(p), exp(e) {}

    //sum e = 0 to exp of (prime ^e)
    Val getContribution() const {
        Val ppc;
        auto it = primePowCache.find(prime);
        if (it == primePowCache.end()) {
            ppc = myPow(prime-1, MODNUM-2);
            primePowCache.insert(make_pair(prime, ppc));
        } else {
            ppc = it->second;
        }
        Val ans = (myPow(prime, exp+1) + MODNUM - 1) * (ppc);
        ans %= MODNUM;

        return ans;
    }
};

PFactor extractPrime(Val& num, Val prime) {
    PFactor ret(prime, 0);
    while ((num % prime) == 0) {
        num /= prime;
        ret.exp++;
    }
    return ret;
}

vector<PFactor> extractPrimeFact(Val num) {
    vector<PFactor> retval;
    int pind = 0;
    while (primes[pind] <= num) {
        //std::cout << "Checking " << primes[pind] << std::endl;
        if (num % primes[pind]) {
            pind++;
            continue;
        }

        PFactor pf = extractPrime(num, primes[pind++]);
        //std::cout << "Found pf: (" << pf.prime << ", " << pf.exp << ")" << std::endl;
        retval.push_back(pf);
    }

    return retval;
}

Val sumProperDivisors(const vector<PFactor>& pfs) {
    Val ret = 1;
    for (const PFactor& pf : pfs) {
        ret *= pf.getContribution();
        ret %= MODNUM;
    }
    return ret;
}

vector<PFactor> combineFacts(vector<PFactor>& oldpfs, vector<PFactor>& newpfs) {
    vector<PFactor> ret;
    int oi=0, ni=0;
    while (oi < oldpfs.size() && ni < newpfs.size()) {
        if (oldpfs[oi].prime == newpfs[ni].prime) {
            PFactor ppf(oldpfs[oi].prime, oldpfs[oi].exp + newpfs[ni].exp);
            ret.push_back(ppf);
            oi++; ni++;
        } else if (oldpfs[oi].prime < newpfs[ni].prime) {
            ret.push_back(oldpfs[oi++]);
        } else {
            ret.push_back(newpfs[ni++]);
        }
    }
    if (oi < oldpfs.size()) {
        ret.insert(ret.end(), oldpfs.begin() + oi, oldpfs.end());
    }
    if (ni < newpfs.size()) {
        ret.insert(ret.end(), newpfs.begin() + ni, newpfs.end());
    }
    return ret;
}

int main() {
    generatePrimes(NUMLIMIT);

    Val n; std::cin >> n;
    int q; std::cin >> q;

    vector<PFactor> oldpfs = extractPrimeFact(n);

    for (int qi=0; qi<q; qi++) {
        Val x; std::cin >> x;

        vector<PFactor> newpfs = extractPrimeFact(x);
        oldpfs = combineFacts(oldpfs, newpfs);
        Val ans = sumProperDivisors(oldpfs);

        std::cout << ans << std::endl;
    }
}
