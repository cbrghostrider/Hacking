import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 

-- (Num people, shyness level)
type Problem = [(Int, Int)]
type Result  = Int 

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

writeOutput :: [Result] -> [String]
writeOutput = writeOutput' 1
  where writeOutput' _ [] = []
        writeOutput' n (r:rs) = ("Case #" ++ (show n) ++ ": " ++ (writeResult r)) : writeOutput' (n+1) rs

processInput :: String -> String
processInput = unlines . writeOutput . map solveProblem . parseProblem . tail . lines

writeResult :: Result -> String
writeResult = show

charToInt :: Char -> Int
charToInt '0' = 0
charToInt '1' = 1
charToInt '2' = 2
charToInt '3' = 3
charToInt '4' = 4
charToInt '5' = 5
charToInt '6' = 6
charToInt '7' = 7
charToInt '8' = 8
charToInt '9' = 9

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (s:ss) = (zip (map charToInt . last . words $ s) [0..])  : parseProblem ss

solveProblem :: Problem -> Result
solveProblem = fst . foldl' (\(numInv, numAcc) (num, shy) -> 
                                 if numAcc < shy then (numInv + (shy - numAcc), (numAcc + (shy - numAcc) + num)) 
                                                 else (numInv, numAcc + num))
                            (0, 0)


