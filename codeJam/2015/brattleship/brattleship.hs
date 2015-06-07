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

type Problem = (Int, Int, Int)
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
parseProblem (ns:ss) = (r, c, w) : parseProblem ss
  where (r, c, w) = (\[r, c, w]->(r, c, w)). map read. words $ ns

solveProblem :: Problem -> Result
solveProblem (r, c, w) = 
  let fullCalls = (r-1) * (c `div` w)
      partCalls = (c `div` w) - 1
      remCalls  = if c `mod` w == 0 then w else 3 + w - 2
      lastRowCalls = partCalls + remCalls
  in  fullCalls + lastRowCalls


