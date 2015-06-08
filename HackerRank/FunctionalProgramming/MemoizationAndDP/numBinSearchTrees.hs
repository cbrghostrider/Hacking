-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Array

limit :: Int
limit = 1001

cache = listArray (0, limit) [numBinTrees n | n <- [0..limit]] 

numBinTrees :: Int -> Integer 
numBinTrees 0 = 1
numBinTrees 1 = 1
numBinTrees n = sum . map (\lhs -> (cache ! lhs) * (cache ! (n-lhs-1))) $ [0..n-1]

main :: IO ()
main = do
  ip <- getContents
  let ns    = map read . tail . lines $ ip
  mapM_ (putStrLn . show) $ map ((`mod` (10^8 + 7)) . (numBinTrees)) ns
