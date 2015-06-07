-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

bigGCD :: [Integer] ->[Integer] -> Integer
bigGCD ns ms = gcd (reduce ns) (reduce ms)
  where reduce = foldl' (*) 1

main :: IO ()
main = do 
  nstr  <- getLine
  nsstr <- getLine
  mstr  <- getLine
  msstr <- getLine
  let ans = (`mod` (10^9 + 7)) $ bigGCD (map read . words $ nsstr) (map read . words $ msstr)
  putStrLn $ show ans
