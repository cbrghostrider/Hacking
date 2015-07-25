-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Char

checkStatus :: [String] -> (Int, Int) -> Bool
checkStatus grid (r, c) = 
  let coords = [(r-1, c), (r+1, c), (r, c-1), (r, c+1)]
      eval (rv, cv) = digitToInt . (!! cv) . (!! rv) $ grid
      myval  = eval (r, c)
  in  null . filter (>= myval) . map eval $ coords

solveCell :: Int -> [String] -> (Int, Int) -> Char
solveCell len grid (r, c) = 
  if (r == 0) || (r == (len-1)) || (c == 0) || (c == (len-1)) || (checkStatus grid (r, c) == False)
     then (grid !! r) !! c
     else 'X'

solveLine :: Int -> [String] -> Int -> String
solveLine len grid linenum = map (\c -> solveCell len grid (linenum, c)) $ [0..(len-1)] 

solveProblem :: Int -> [String] -> [String]
solveProblem len grid = map (solveLine len grid) $ [0..(len-1)]

main :: IO ()
main = do
  ip <- getContents
  let nlen = read . head . lines $ ip
      grid = tail . lines $ ip
      ansgrid = solveProblem nlen grid
  mapM_ putStrLn ansgrid
  
