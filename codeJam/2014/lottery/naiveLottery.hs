import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 
import Data.Bits

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
parseProblem (ns:ss) = ((\[a, b, k] -> (a, b, k)) . map read . words $ ns) : parseProblem ss

solveProblem :: Problem -> Result
solveProblem l@(a, b, k) = length . filter (< k) . map (\(n1, n2) -> n1 .&. n2) $ [(m1, m2) | m1 <- [0..a-1], m2 <- [0..b-1]]


