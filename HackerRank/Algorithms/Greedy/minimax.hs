-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List
import Data.Ord

minDiffFrom :: Int -> [Int] -> Int
minDiffFrom fromme = minimum . map ((abs) . (\x -> fromme - x))

solveProblem :: Int -> Int -> [Int] -> Int
solveProblem p q ns = 
  let ns' = sort ns
      pcand = minDiffFrom p ns'
      qcand = minDiffFrom q ns'
      mids  = filter (\(x, dx)-> (x >= p) && (x <= q)) . reverse . snd .
                foldl' (\a@(ln, ls) nn -> (nn, ((ln+nn) `div` 2, (nn-ln) `div` 2):ls)) (head ns', []) $ tail ns'
      allCands = (p, pcand):(q, qcand):mids
      maxdelta = maximum . map snd $ allCands 
      chosen = head . sort . map fst . filter ((== maxdelta) . snd) $ allCands
  in  chosen 

main :: IO ()
main = do
  _     <- getLine
  nsstr <- getLine
  pqstr <- getLine
  let ns     = map read . words $ nsstr
      [p, q] = map read . words $ pqstr
      ans    = solveProblem p q ns 
  putStrLn $ show ans
