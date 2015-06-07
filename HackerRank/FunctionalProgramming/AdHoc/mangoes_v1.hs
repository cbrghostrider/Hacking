-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- this code currently times out on the biggest inputs
-- the problem is that I am increasing f by 1 at each step.
-- I need to binary search the space instead
import Data.List

-- computes the fewest mangoes consumed when number of friends in the party are fixed to f
mangoesConsumed :: [Int] -> [Int] -> Int -> Int
mangoesConsumed as hs f = sum . take f . sort . map (\(a, h) -> a + (f-1)*h) $ zip as hs


-- try picking # of friends from 0, 1, 2, ... until constraint is broken
solveProblem :: [Int] -> [Int] -> [Int] -> Int
solveProblem [n, m] as hs = fst . last . takeWhile ((<=m) . snd) . zip [0..] . map (mangoesConsumed as hs) $ [0..(length as)]

main :: IO ()
main = do 
  nmstr <- getLine
  asstr <- getLine
  hsstr <- getLine
  putStrLn $ show $ solveProblem (map read . words $ nmstr) (map read . words $ asstr) (map read . words $ hsstr)
