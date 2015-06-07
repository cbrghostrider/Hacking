-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 

-- FIXME: Change these
type Problem = [Int]
type Result  = (Int, Int)

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

writeOutput :: [(Int, Result)] -> [String]
writeOutput = map (\(i, r) -> ("Case #" ++ (show i) ++ ": " ++ (writeResult r)))

processInput :: String -> String
processInput = unlines . writeOutput . zip [1..] . map solveProblem . parseProblem . tail . lines

writeResult :: Result -> String
writeResult (x, y) = (show x) ++ " " ++ (show y)

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (_:ns:ss) = (map read . words $ ns) : parseProblem ss

solveMethod1 :: Problem -> Int
solveMethod1 (n:ns) = fst . foldl' (\(sum, last) num -> if num < last then (sum + (last-num), num) else (sum, num)) (0, n) $ ns

solveMethod2 :: Problem -> Int
solveMethod2 (n:ns) = 
  let max = maximum (n:ns)
      eatenPer10s = fst . foldl' (\(maxdiff, last) num -> if (last - num > maxdiff) then (last-num, num) else (maxdiff, num)) (0, n) $ ns
      eaten = map (\num -> if num < eatenPer10s then num else eatenPer10s) . init$ (n:ns)
  in  sum eaten

solveProblem :: Problem -> Result
solveProblem ns = (solveMethod1 ns, solveMethod2 ns)


