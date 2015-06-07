-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import System.Environment (getArgs)
import Data.Ord
import Data.List

-- (tests supported, tests not supported, factor)
type Problem = (Int, Int, Int)

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

writeOutput :: [Int] -> [String]
writeOutput = writeOutput' 1
  where writeOutput' _ [] = []
        writeOutput' n (x:xs) = ("Case #" ++ (show n) ++ ": " ++ (show x)) : writeOutput' (n+1) xs

solveProblem :: Problem -> Int
solveProblem pblm@(l, p, c) =  
  let multiples = map ( ($ c) . (\x -> (^x)) . (2^) ) $ [0, 1..]
      equations = map (\v -> l*v >= p) $ multiples
      tests     = dropWhile ((==False) . snd) . zip [0, 1..] $ equations
  in  fst . head $ tests

processInput :: String -> String 
processInput = unlines . writeOutput . map solveProblem . map ((\[l, p, c] -> (read l, read p, read c)) . words) . tail . lines 



