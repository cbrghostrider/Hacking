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

writeOutput :: [(Int, Result)] -> [String]
writeOutput = map (\(i, r) -> ("Case #" ++ (show i) ++ ": " ++ (writeResult r)))

processInput :: String -> String
processInput = unlines . writeOutput . zip [1..] . map solveProblem . parseProblem . tail . lines

writeResult :: Result -> String
writeResult = undefined

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem _  = undefined

solveProblem :: Problem -> Result
solveProblem = undefined


