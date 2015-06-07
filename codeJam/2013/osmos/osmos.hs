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
import Debug.Trace

type Mote    = Integer
type Problem = (Mote, [Mote])
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
parseProblem (an:ns:ss) = 
  let [a, n] = map read . words $ an
      nums   = map read . words $ ns
  in  (a, nums) : parseProblem ss

-- x, 2x - 1, 4x - 3, 8x - 7 ....
sumAbsorbedMotes :: Mote -> Int -> Mote
sumAbsorbedMotes x i = (2^i)*x - (2^i - 1) 

-- computes number of motes needed to absorb the next one
-- binary search the range, to get log N instead of N efficiency
computeNumMotes :: Mote -> Mote -> Int -> Int -> Int
computeNumMotes curMote tgtMote loGuess hiGuess = 
  let midGuess = (loGuess + hiGuess) `div` 2
      loSum = sumAbsorbedMotes curMote loGuess
      midSum= sumAbsorbedMotes curMote midGuess
      hiSum = sumAbsorbedMotes curMote hiGuess
  in  if loGuess + 1 >= hiGuess  -- can't binary search anymore
         then if loSum >= tgtMote
                 then loGuess
                 else if hiSum >= tgtMote
                         then hiGuess
                         else error "Probably initial bounds for guesses incorrect"
         else if loSum == tgtMote
                 then loGuess
                 else if hiSum == tgtMote
                         then hiGuess
                         else if (midSum > tgtMote)
                                 then computeNumMotes curMote tgtMote loGuess  midGuess
                                 else computeNumMotes curMote tgtMote midGuess hiGuess

solveProblem' :: Problem -> Result
solveProblem'    (_, []) = 0
solveProblem'    (1, ms) = length ms
solveProblem' pb@(a, ms) = 
  let m   = head ms
      ms' = tail ms
      loGuess = 0
      hiGuess = fromIntegral $ (m `div` a) + 1
      num = computeNumMotes a (m+1) loGuess hiGuess
      val = sumAbsorbedMotes a num 
      numRec = solveProblem' (val, ms)
  in  if a > m
         then solveProblem' ((a + m), ms')
         else if (num > length ms) || (num == 0) || (num + numRec >= length ms)
                 then length ms -- delete everything that is left
                 else num + numRec

solveProblem :: Problem -> Result
solveProblem pb@(a, ms) = solveProblem' (a, sort ms)


