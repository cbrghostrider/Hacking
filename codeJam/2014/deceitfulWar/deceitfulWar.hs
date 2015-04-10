-- Author: Sourabh S Joshi
-- Problem: https://code.google.com/codejam/contest/2974486/dashboard#s=p3&a=0

import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 

type Weight = Double
type Problem = ([Weight], [Weight])

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

writeOutput :: [(Int, Int)] -> [String]
writeOutput = writeOutput' 1
  where writeOutput' _ [] = []
        writeOutput' n ((s1, s2):xs) = ("Case #" ++ (show n) ++ ": " ++ (show s1) ++ " " ++ (show s2)) : writeOutput' (n+1) xs

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (_ : ns : ks : ps) = ((map read . words $ ns) , (map read . words $ ks)) : parseProblem ps

-- UNFAIR GAME: Naomi's cheating strategy
-- At each step
--   if Naomi smallest is smaller than Ken's smallest
--     she will pick her smallest block, and tell ken the weight as wkl - delta
--     where wkl is weight of ken's largest block for CURRENT iteration
--     and delta is a very small number
--     this will force ken to play his smallest weight that is bigger than naomi's, to beat naomi's weight
--     which in fact is his largest weight
--   else 
--     pick naomi's weight that is just larger than ken's smallest
--     tell ken this weight is larger than his largest remaining
--     then ken will play his smallest against this weight
--     and naomi will win (without having wasted any weight larger than it needs to be)
playDeceitStep :: (Int, Problem) -> (Int, Maybe Problem)
playDeceitStep (inScore, pb@(ns, ks)) = 
  let smallN = head ns  -- Naomi's smallest
      largeK = last ks  -- Ken's largest
      smallK = head ks  -- Ken's smallest
      smallPlayN = dropWhile (< smallK) ns -- Naomi's weight that is just larger than ken's smallest
  in  if null ks && null ns
         then (inScore, Nothing)
         else if smallN < smallK  -- Naomi's smallest is smaller then Ken's smallest
                 then (inScore, Just ((tail ns), (init ks))) -- make Ken waste his largest to beat it (by telling him that wt - delta)
                 else if null smallPlayN -- well shoot, ken's smallest is bigger than naomi's largest wt, she's gonna lose all remaining
                         then (inScore, Nothing)
                         else (inScore + 1, Just ((ns \\ [head smallPlayN]), (tail ks))) -- pick Naomi's smallest weight that is bigger than Ken's smallest
                                                                                         -- tell ken that this weight is his biggest + delta, 
                                                                                         -- so he plays his smallest against it

-- FAIR GAME: Ken's optimal strategy
-- At Each Step
--   If naomi plays weight x, Ken will play his smallest weight larger than x
--   if no such weight exists for ken, then he will play his smallest weight
--   thus when ken win's he will win with the worst possible weight
--   and when he loses, he will lose with the most useless weight
--   this is ken's optimal strategy
playWarStep :: (Int, Problem) -> (Int, Maybe Problem)
playWarStep (inScore, pb@(ns, ks)) = 
  let playN  = last ns  --naomi plays this
      ks'    = dropWhile (< playN) ks
      playK  = head ks' -- ken beats her with this
      playK' = head ks  -- or ken loses with his lowest weight
  in  if null ks && null ns
         then (inScore, Nothing)
         else if null ks' 
                 then (inScore+1, Just ((init ns), (ks \\ [playK'])))
                 else (inScore  , Just ((init ns), (ks \\ [playK ])))

solveWar :: ((Int, Problem) -> (Int, Maybe Problem)) -> Int -> Problem -> Int
solveWar warGameF inScore pb@(ns, ks) =
  let oneStep@(score, pblm) = warGameF (inScore, pb)
      pblm' = fromMaybe ([], []) pblm
  in  if pblm == Nothing then score else solveWar warGameF score pblm'

solveProblem :: Problem -> (Int, Int)
solveProblem p@(ns, ks) = (solveWar playDeceitStep 0 (sort ns, sort ks), solveWar playWarStep 0 (sort ns, sort ks))

processInput :: String -> String
processInput = unlines . writeOutput . map solveProblem . parseProblem . tail . lines


