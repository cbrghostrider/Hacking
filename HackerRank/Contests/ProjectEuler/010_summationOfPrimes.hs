-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

--primesUpTo num = sieve [2..num]
primesUpTo' :: Integer -> [Integer] -> [Integer]
primesUpTo' _ [] = []
primesUpTo' num (l:ls) = l : primesUpTo' num (filter (\x -> x `mod` l /= 0) ls)

primesUpTo :: Integer -> [Integer]
primesUpTo n = primesUpTo' n [2..n]

-- Project Euler: Problem 10
ans10 :: Integer -> Integer
ans10 n = sum.primesUpTo $ n

main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
  mapM_ (putStrLn . show) $ map ans10 ns
