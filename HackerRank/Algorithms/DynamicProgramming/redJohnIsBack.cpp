// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;

// primes less than n
// this is from my leetcode solution
int primesUpTo(int n) {
    if (n <= 2)  return 0;

    vector<bool> sieve(n/2, false); //don't consider even numbers
    int primes = 1; 		        //account for prime 2

    for (int ind=1; ind<sieve.size(); ind++) {  //iterate through the odd numbers
        if (sieve[ind] == false) { 	            //found a prime
            primes++;
            int num = 2*ind + 1;	            //and this is the number
            for (int ni=num+num; ni < n; ni+=num) {
                if (ni%2) sieve[ni/2] = true;   //mark its odd multiple 
            }
        }
    }
    return primes;
}

int solveProblem(int n) {
    vector<int> cache(n+1, 0);
    if (n <= 3) return primesUpTo(1 + 1);
    if (n == 4) return primesUpTo(2 + 1);

    cache[1] = cache[2] = cache[3] = 1;
    cache[4] = 2;

    for (int c=5; c<n+1; c++) {
        cache[c] = cache[c-4] + cache[c-1];
    }

    return primesUpTo(cache[n] + 1);
}

int main() {
    int t, n;
    std::cin >> t;
    for (int i=0; i<t; i++) {
        std::cin >> n;
        int ans = solveProblem(n);
        std::cout << ans << std::endl;
    }
}
