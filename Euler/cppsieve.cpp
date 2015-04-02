#include <vector>
#include <stdio.h>
#include <ostream>
#include <iostream>

std::vector<int> generate_primes( int n )
{
    std::vector<bool>sieve( n, true ) ;
    std::vector<int> primes ;
    for( std::size_t i = 2 ; i < sieve.size() ; ++i ) 
        if( sieve[i] ) {
            primes.push_back(i);
            //std::cout << "Prime: " << i << std::endl;
            for( std::size_t j = i*2 ; j < sieve.size() ; j += i ) {
                sieve[j] = false ;
            }
        }

    return primes ;
} 

int main () {
    std::vector<int> primes = generate_primes(2000000);
    long long int sum=0;
    for (std::size_t i=0; i<primes.size(); i++) {
        sum += primes[i];
    }
    std::cout << "Sum is: " << sum << std::endl;
}


