class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;

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
};
