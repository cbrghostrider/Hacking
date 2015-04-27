-- O(N . E^2) solution. Not terribly efficient, but easy and good for small input
import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 
import Data.Array

type Energy  = Integer
type Value   = Integer 
type Problem = (Energy, Energy, [Value])
type Result  = Value

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
parseProblem (er:vs:ss) = 
  let [e, r, n] = map read . words $ er
      vs' = map read . words $ vs
  in  (e, r, vs') : parseProblem ss

solveDynProg :: Problem -> Result
solveDynProg (e, r, vs) = go bh e
  where 
    -- takes current #items, and current Energy- solves for optimum value
    go :: Integer -> Energy -> Value
    go i x
      | i == 0 = 0
      | otherwise = maximum . map (\(j, xp) -> (arr ! ((fromIntegral i-1), xp)) + (vs !! fromIntegral (i-1))*j) . 
                     map (\j->(j, (if (x-j+r) > e then e else (x-j+r)))) $ [0..x]
    bh     = ((fromIntegral . length $ vs) )
    bounds = ((0, 0), (bh, e))
    arr = listArray bounds [go idx enrg | idx <- [0..bh], enrg <- [0..e] ]

solveProblem :: Problem -> Result
solveProblem (e, r, vs) = let vs' = reverse vs in  solveDynProg (e, r, vs')


