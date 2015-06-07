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
type Result  = Bool

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
writeResult True  = "GOOD"
writeResult False = "BAD"

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (_:ns:ss) = (map read . words $ ns) : parseProblem ss

-- all numbers have equal probability of being found at a position
-- so about half the numbers are at indices bigger, and other half smaller
numGood :: Int
numGood = 500

-- this is skewed 
numBad :: Int
numBad  = 472

solveProblem :: Problem -> Result
solveProblem ns = 
  let numgt = length . filter (==True) . map (\(i, v) -> if v <= i then True else False) . zip [0..] $ ns
      midpt = numBad + (numGood - numBad) `div` 2
  in  if numgt >= midpt then True else False


