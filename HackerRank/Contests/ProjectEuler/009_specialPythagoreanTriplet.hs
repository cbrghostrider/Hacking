-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

-- Project Euler: Problem 9
ans9 :: Int -> Int
ans9 n = 
  let trips = [(a, b, n - a - b) | b <- [1..(n `div` 2)], a <- [1..b], a^2 + b^2 == (n-a-b)^2]
  in  if null trips then -1 else maximum . map (\(a, b, c)->a*b*c) $ trips

main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
  mapM_ (putStrLn . show) $ map ans9 ns
