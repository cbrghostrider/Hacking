import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 
import Data.Bits

type Problem = (Integer, Integer, Integer)
type Result  = Integer 
{-
main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)
-}
writeOutput :: [(Integer, Result)] -> [String]
writeOutput = map (\(i, r) -> ("Case #" ++ (show i) ++ ": " ++ (writeResult r)))

processInput :: String -> String
processInput = unlines . writeOutput . zip [1..] . map solveProblem . parseProblem . tail . lines

writeResult :: Result -> String
writeResult = show

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (ns:ss) = ((\[a, b, k] -> (a, b, k)) . map read . words $ ns) : parseProblem ss

-- bits to represent integers LESS THAN a value
bitsToRepresent :: Integer -> Int
bitsToRepresent x = 1 + (fst . last . takeWhile ((< x) . snd) . zip powers . map (2^) $ powers)
  where powers = [0..]

solveProblem :: Problem -> Result
solveProblem l@(a, b, k) = undefined 

-- TODO --

-- Think about bit representations for a, b, k
-- For each bit from position 0, 1, ...
-- if it is 1 in k, corresponding bits in a and b HAVE to be fixed to 1, so it contributes only 1 combo
-- if it is 0, corresponding a and b bits could be (0, 0), (0, 1), (1, 0) so 3 combos
--    or more precisely, if that bit is still AVAILABLE to change (if k < a and k < b) then above is true
-- if that bit isn't available to change (either becasue k > a and you passed bitsToRepresent a
--                                        or because k > b and you passed bitsToRepresent b)
--    then that portion (a or b) only have 1 combo to offer
--    so for example if the above condition holds for a but not b, a's bit is fixed at 0, but b's can be 0 or 1, so 2 combos
--
-- set counter = 0
-- now set up a loop that goes from 0 to k-1 (call the loop variable num)
--   and count how many bits are set to 1 in num = n1s
--   and therefore (bitsToRepresent k) - n1s = n0s
--   depending on relative values of a, b, k, and which bit we are at, 
--   add combinations of 3 ^ n0s or 2^ n0s or 1 or nothing to the counter
--
-- at the end of the loop, we have our answer
