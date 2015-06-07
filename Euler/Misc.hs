-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
module Misc where

import Data.List 

isPrime :: Integer -> Bool
isPrime 0 = False
isPrime 1 = False
isPrime 2 = True
isPrime n = 
  let listChk = [2..endChk]
      endChk = (1 + (truncate.sqrt.fromIntegral $ n)) :: Integer
  in not . or . map (\x -> n `mod` x == 0) $ listChk 

sieve :: [Integer] -> [Integer]
sieve [] = []
sieve (x : xs) = x : sieve [x' | x' <- xs, x' `mod` x /= 0]

primeNumbers :: [Integer]
primeNumbers = sieve [2..]

--primesUpTo num = sieve [2..num]
primesUpTo' :: Integer -> [Integer] -> [Integer]
primesUpTo' _ [] = []
primesUpTo' num (l:ls) = l : primesUpTo' num (filter (\x -> x `mod` l /= 0) ls)

primesUpTo :: Integer -> [Integer]
primesUpTo n = primesUpTo' n [2..n]

primeFactors :: Integer -> [Integer]
primeFactors val 
  | val `mod` 2 == 0 = 2 : primeFactors (val `div` 2)
  | otherwise = sieveList val divList 
   where 
    divList = [3, 5..num] :: [Integer]
    num = 1 + (truncate . sqrt . fromIntegral $ val)::Integer
    sieveList 0 _  = []
    sieveList _ [] = []
    sieveList n (l:ls) 
      | n `mod` l == 0 = l : sieveList (n `div` l) ls
      | otherwise      = sieveList n ls
  
isPalindrome :: (Eq a) => [a] -> Bool
isPalindrome xs = xs == reverse xs

factors' :: Integer -> [Integer]
factors' n = map fst . filter (\ (x, y) -> y == 0) . zip [1..n] . map (n `mod`) $ [1..n']
  where n' = (1 + (truncate.sqrt.fromIntegral $ n))::Integer

factors :: Integer -> [Integer]
factors n = nub (factList ++ modList)
  where factList = factors' n
        modList = map (n `div` ) factList

triNums :: [Integer]
triNums = scanl1 (+) [1..] 

