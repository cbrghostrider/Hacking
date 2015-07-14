-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Text.Printf
import Data.List

-- unbiased coin, probability of landing heads is 0.5
-- Expected value is sum(pi*vi) for all i
computeExpectedValue :: [Int] -> Double
computeExpectedValue = foldl' (\acc n -> (fromIntegral n)* 0.5 + acc) 0.0

main :: IO ()
main = do
  nstr <- getContents
  let ns = map read . tail . lines $ nstr
  putStrLn . printf "%.1f\n" $ computeExpectedValue ns
