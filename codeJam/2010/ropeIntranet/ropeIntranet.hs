-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import System.Environment (getArgs)
import Data.Ord
import Data.List

type Wire    = (Int, Int)
type Problem = [Wire]

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

writeOutput :: [Int] -> [String]
writeOutput = writeOutput' 1
  where writeOutput' _ [] = []
        writeOutput' n (x:xs) = ("Case #" ++ (show n) ++ ": " ++ (show x)) : writeOutput' (n+1) xs

getProblems :: [String] -> [Problem]
getProblems [] = []
getProblems (n:xs) = getProblem (take (read n) xs) : getProblems (drop (read n) xs)
  where getProblem = map ((\[a, b] -> (a, b)) . map read . words) 

solveProblem :: [Wire] -> Int
solveProblem []     = 0
solveProblem (w:ws) = let (wa, wb) = w in (length . filter ((< wb) . snd) $ ws) + solveProblem ws

-- sort on a coord
sortWires :: [Wire] -> [Wire]
sortWires = sortBy (comparing fst)

processInput :: String -> String
processInput = unlines . writeOutput . map (solveProblem . sortWires ) . getProblems . tail . lines

