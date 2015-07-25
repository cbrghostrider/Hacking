-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

type Problem = (Int, Int)
type Contest = [Problem]

isBalanced :: Contest -> Bool
isBalanced []  = True
isBalanced bds = fst . foldl' (\acc@(tv, (pb, pd)) (b, d) -> (tv && (b > pb) && (d > pd), (b, d))) (True, head bds) $ tail bds

solveProblem :: Contest -> Bool
solveProblem  = not . null . filter isBalanced . permutations 

main :: IO ()
main = do
  ip <- getContents
  let bds = map ((\[b, d]->(b, d)) . map read . words) . lines $ ip
  let ans = solveProblem bds
  putStrLn $ if ans == True then "1" else "0"
