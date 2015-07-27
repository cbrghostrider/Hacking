-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List
import Data.Ord

solveProblem :: [(Int, Int)] -> [Int]
solveProblem = map fst . sortBy (comparing snd) . zip [1..] . reverse . foldl' (\acc (t, d) -> (t+d):acc) []

main :: IO ()
main = do
  ip <- getContents
  let tds = map ((\[t, d] -> (t, d)) . map read . words). tail . lines $ ip
  let ans = solveProblem tds
  putStrLn $ unwords . map show $ ans
  
