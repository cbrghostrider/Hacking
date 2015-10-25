-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

-- The Haskell version is slower, but still correct
-- Including only for completeness

import Data.List

-------------------------------------------------------------------------------
-- Credit : The following (efficient) sieve is not my code
primels :: [Integer]
primels = 2 : filter (isPrime primels) [3,5..]
  where isPrime (p:ps) n = p*p > n || n `rem` p /= 0 && isPrime ps n
-- End credit.        
-------------------------------------------------------------------------------

type PFactor = (Integer, Integer)

c_MODNUM :: Integer
c_MODNUM = 1000000007

getContribution :: PFactor -> Integer
getContribution (pr, ex) = (pr ^ (ex + 1) - 1) `div` (pr - 1)

sumProperDivisors :: [PFactor] -> Integer
sumProperDivisors = foldl' (\ acc elem -> acc * getContribution elem) 1

combineFacts :: [PFactor] -> [PFactor] -> [PFactor]
combineFacts [] ys = ys
combineFacts xs [] = xs
combineFacts ((x@(px, ex)):xs) ((y@(py, ey)):ys) 
  | px == py  = (px, ex + ey) : combineFacts xs ys
  | px < py   = x : combineFacts xs (y:ys)
  | otherwise = y : combineFacts (x:xs) ys

countTimes :: Integer -> Integer -> Integer
countTimes n p = if (n `mod` p == 0) then 1 + countTimes (n `div` p) p else 0

countPrimeTimes :: Integer -> Integer -> (Integer, PFactor)
countPrimeTimes n p = (newn, factor) 
  where factor = (p, countTimes n p)
        newn   = n `div` (p ^ (snd factor))

extractPrimeFact :: [Integer] -> Integer -> [PFactor]
extractPrimeFact [] _ = []
extractPrimeFact (p:ps) num 
  | num <= 1       = []
  | p > num        = []
  | (num `mod` p) == 0 = let (nn, pf) = countPrimeTimes num p in (pf : extractPrimeFact ps nn)
  | otherwise      = extractPrimeFact ps num

runQueries :: Int -> [Integer] -> [PFactor] -> IO ()
runQueries 0 _ _ = return ()
runQueries q primes oldpfs = do
  xstr <- getLine
  let x = read xstr
  let xpfs = extractPrimeFact primes x
  let newpfs = combineFacts oldpfs xpfs
  let ans = (sumProperDivisors newpfs) `mod` c_MODNUM
  putStrLn $ show ans
  runQueries (q-1) primes newpfs 


main :: IO ()
main = do 
  nqstr <- getLine 
  let allPrimes = take 10000 primels
  let [nstr, qstr] = words nqstr
      n = read nstr
      q = read qstr
  let oldpfs = extractPrimeFact allPrimes n
  runQueries q allPrimes oldpfs
  

