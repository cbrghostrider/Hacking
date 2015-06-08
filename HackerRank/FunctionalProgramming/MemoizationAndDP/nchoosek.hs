-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Array

limit :: Int
limit = 1001

cache = listArray ((0,0), (limit, limit)) [nchoosek n k | n <- [0..limit], k <- [0..limit]] 

nchoosek :: Int -> Int -> Integer 
nchoosek n k
  | n <= k  = 1
  | k == 0  = 1
  | otherwise = (cache ! (n-1, k-1)) + (cache ! (n-1, k))

main :: IO ()
main = do
  ip <- getContents
  let nsstr = tail . lines $ ip
  let nks    = map ((\[n, k]->(n, k)) . map read . words) nsstr
  mapM_ (putStrLn . show) $ map (\(n, k) -> (nchoosek n k) `mod` (10^8 + 7)) nks 
