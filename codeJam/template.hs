import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 

-- FIXME: Change these
type Problem = Int
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
writeResult = undefined

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem _  = undefined

solveProblem :: Problem -> Result
solveProblem = undefined


