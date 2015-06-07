-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 
import Data.Array
import Control.Monad
import Debug.Trace

type Problem = (Int, Int, Int, [Int])
type Result  = Int 

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
writeResult = show

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (ns:ds:ss) = (c, d, v, denos) : parseProblem ss
  where 
    (c, d, v) = (\[c, d, v]->(c, d, v)) . map read . words $ ns
    denos     = map read . words $ ds

powerset :: [a] -> [[a]]
powerset = filterM (const [True, False])

-- given a list of denos, what vals can I make (with only 1 of each)
evalValues :: [Int] -> [Int]
evalValues ds = sort . map sum . init . powerset $ ds
      
-- given a sequence of values that we can currently make, what deno should I add
getNextNeeded :: [Int] -> Int
getNextNeeded [v]        = v+1
getNextNeeded (v1:v2:vs) = if v1 + 1 == v2 then getNextNeeded (v2:vs) else v1 + 1

solveProblem' :: Problem -> Result
solveProblem' (c, d, v, denos) = 
  let vals    = nub . evalValues $ denos
      newDeno = getNextNeeded vals
  in  if newDeno > v then 0 else if newDeno == v then 1 else (1 + solveProblem' (c, d+1, v, (denos ++ [newDeno])))

solveProblem :: Problem -> Result
solveProblem (c, d, v, denos) = 
  if 1 `elem` denos then solveProblem' (c, d, v,denos) else 1 + solveProblem' (c, d+1, v, (1:denos))
