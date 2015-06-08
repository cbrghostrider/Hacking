-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Array

cache = listArray (0, 100001) [pentagonalNums n | n <- [0..100001]] 

pentagonalNums :: Int -> Int
pentagonalNums 0 = 0
pentagonalNums 1 = 1
pentagonalNums n = (n-1) * 3 + 1 + (cache ! (n-1))

main :: IO ()
main = do
  ip <- getContents
  mapM_ (putStrLn . show) $ map (pentagonalNums) (map read . tail . lines $ ip) 
