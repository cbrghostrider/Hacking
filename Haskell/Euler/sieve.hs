main = print $ solve where
  solve = sum $ primes 2000000 where
    primes n = sieve $ 2:[3,5..n] where
      sieve (p:xs) | p*p > n = xs
                   | True = p:sieve [x | x <- xs, mod x p /= 0]

