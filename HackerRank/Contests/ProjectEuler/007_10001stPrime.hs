-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
sieve :: [Integer] -> [Integer]
sieve [] = []
sieve (x : xs) = x : sieve [x' | x' <- xs, x' `mod` x /= 0]

primeNumbers :: [Integer]
primeNumbers = sieve [2..]

-- Project Euler: Problem 7
ans7 :: Integer -> Integer
ans7 n = head . reverse . take (fromIntegral n) $ primeNumbers 

main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
  mapM_ (putStrLn . show) $ map ans7 ns
