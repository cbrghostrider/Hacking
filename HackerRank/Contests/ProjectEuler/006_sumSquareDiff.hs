-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- Project Euler: Problem 6
ans6 :: Integer -> Integer
ans6 n = ((^2).sum $ listNums) - (sum. map (^2) $ listNums)
  where listNums = [1..n]

main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
  mapM_ (putStrLn . show) $ map ans6 ns
