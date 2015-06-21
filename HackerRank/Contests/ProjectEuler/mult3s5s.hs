-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
numks k n = (n-1) `div` k

sumFirstk k = (k*(k+1)) `div` 2

mult35 n = 
  let n3 = numks 3 n
      n5 = numks 5 n
      n15 = numks 15 n
      sum3s = 3 * sumFirstk n3
      sum5s = 5 * sumFirstk n5
      sum15s = 15 * sumFirstk n15
  in  sum3s + sum5s - sum15s

main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
  mapM_ (putStrLn . show) $ map mult35 ns
