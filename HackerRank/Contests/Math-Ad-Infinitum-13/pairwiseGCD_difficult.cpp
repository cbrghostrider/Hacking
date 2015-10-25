// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------

// Note that 9/25 tests TLE, while rest pass successfully

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>

using std::pair;
using std::make_pair;
using std::unordered_map;
using std::vector;

typedef long long Val;

const Val MODNUM = 1234567891;
const int LIMIT  = 100000; 
const int PNUMLIMIT = 100050;

vector<Val> primes;
double THRESHOLD = 0.9;
bool usecache = false;
unordered_map<Val, Val> cachegcd;
inline Val makeKey(Val ai, Val aj) {
    return (((ai) << 32) | (aj));
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

// Sieve of Eratosthenes
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

class PWgcd {
public:
    PWgcd(int n, int m);
    Val computeGcds();
private:
    Val evalPoly(Val x);
    void precomputePFacts(vector<Val>& aas);
    inline Val gcd(Val a, Val b);
    
    const int N, M;
    vector<Val> as;
    vector<Val> bs;
    vector<bool> psbools;
    vector<Val> ps;
    vector<vector<PFactor>> pfacts;
    Val ret;
};

PWgcd::PWgcd(int n, int m)
: N(n), M(m), 
  as(N, 0), bs(M+1, 0),
  psbools(LIMIT+1, false),
  ps(LIMIT+1, 0),
  pfacts(LIMIT+1, vector<PFactor>()),
  ret(0) {
    for (int i=0; i<N; i++) {
        std::cin >> as[i];
    }
    for (int i=0; i<=M; i++) {
        std::cin >> bs[i];
    }
}

Val PWgcd::evalPoly(Val x) {
    Val xv = 1; //x^0
    
    Val ptot = (bs[0] >= 0) ? bs[0] : 0; 
    Val ntot = (bs[0] < 0) ? ((-1)*bs[0]) : 0; 
    
    for (int i=1; i<=M; i++) {
        xv *= x;
        xv %= MODNUM;
        Val term = xv * bs[i];
        if (term >= 0) {
            ptot += term;
            ptot %= MODNUM;
        } else {
            ntot += (-1)*term;
            ntot %= MODNUM;
        }
    }
    Val tot = ((ptot) - (ntot) + MODNUM) % MODNUM;
    return tot;
}

void PWgcd::precomputePFacts(vector<Val>& aas) {
    pfacts[1].push_back(PFactor(1, 1));
    for (int i=0; i<aas.size(); i++) {
        pfacts[aas[i]] = extractPrimeFact(aas[i]);
    }
}

inline Val PWgcd::gcd(Val a, Val b) {
    if (a > b) return gcd(b, a);
    if (a == b) {
        if (psbools[a] == false) {
            ps[a] = evalPoly(a);
            psbools[a] = true;
        }
        return a;
    }

    //Val key = makeKey(a, b);
    //if (usecache) {
    //    auto it = cachegcd.find(key);
    //    if (it != cachegcd.end()) {
    //        return it->second;  
    //    }
    //}

    const vector<PFactor>& afacts = pfacts[a];
    const vector<PFactor>& bfacts = pfacts[b];

    int ai=0, bi=0;
    Val ret = 1;
    while (ai < afacts.size() && bi < bfacts.size()) {
        if (afacts[ai].prime == bfacts[bi].prime) {
            int expo = std::min(afacts[ai].exp, bfacts[bi].exp);
            Val term = myPow(afacts[ai].prime, expo);
            ret *= term;
            ret %= MODNUM;
            ai++; bi++;
        } else if (afacts[ai].prime < bfacts[bi].prime) {
            ai++;
        } else {
            bi++;
        }
    }
    //if (usecache) {
    //    cachegcd.insert(make_pair(key, ret));
    //}
    if (psbools[ret] == false) {
        ps[ret] = evalPoly(ret);
        psbools[ret] = true;
    }
    return ret;
}

Val PWgcd::computeGcds() {
    {
        vector<Val> aas = as;
        std::sort(aas.begin(), aas.end());
        auto it = std::unique(aas.begin(), aas.end());
        aas.resize(std::distance(aas.begin(), it));
        if ((((double)(aas.size()))/((double)(as.size()))) < THRESHOLD) {
            usecache = true;
        }
        precomputePFacts(aas);
    }

    for (int iai=0; iai<N; iai++) {
        for (int iaj=iai+1; iaj<N; iaj++) {
            Val gcdv = gcd(as[iai], as[iaj]);
            Val ep = ps[gcdv];
            ret += ep;
            ret %= MODNUM;
        }
    }
    return ret;
}


int main() {
    generatePrimes(PNUMLIMIT);

    int m, n;
    std::cin >> n >> m;

    PWgcd pw(n, m);
    Val ans = pw.computeGcds();
    std::cout << ans << std::endl;
}

