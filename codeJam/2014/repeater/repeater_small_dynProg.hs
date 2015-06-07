-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- Lazy Dynamic Programming to solve problem
-- https://code.google.com/codejam/contest/2994486/dashboard#s=p0&a=0
import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 
import Data.Array

type Problem = [String]
type Result  = Maybe Int 

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
writeResult Nothing  = "Fegla Won"
writeResult (Just x) = show x

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (n:ss)  = (take num ss) : (parseProblem (drop num ss))
  where num = read n

findResult :: String -> String -> Result
findResult s1in s2in =
  let s1 = ('#': s1in) ++ ['$'] -- pad start and end
      s2 = ('@': s2in) ++ ['&'] -- pad start and end
      go :: Int -> Int -> Result
      go i j 
        | i == 0 && j == 0         = Just 0    -- matched all future ones by add/delete
        | i == 0                   = if (s2 !! j) == (s2 !! (j+1)) 
                                        then (arr ! (i, j-1)) >>= \x -> Just (1+x)
                                        else Nothing
        | j == 0                   = if (s1 !! i) == (s1 !! (i+1)) 
                                        then (arr ! (i-1, j)) >>= \x -> Just (1+x)
                                        else Nothing
        | (s1 !! i) == (s2 !! j)   = arr ! (i-1, j-1) -- don't need add or delete
        | otherwise                = let c1 = if (s1 !! (i+1)) == (s1 !! i) -- delete case
                                                 then (arr ! (i-1, j)) >>= \x -> Just (x + 1)
                                                 else Nothing
                                         c2 = if (s2 !! (j+1)) == (s2 !! j) -- delete case
                                                 then (arr ! (i, j-1)) >>= \x -> Just (x + 1)
                                                 else Nothing
                                         c3 = if (s1 !! (i+1)) == (s2 !! j) -- add case
                                                 then (arr ! (i, j-1)) >>= \x -> Just (x + 1)
                                                 else Nothing
                                         c4 = if (s2 !! (j+1)) == (s1 !! i) -- add case
                                                 then (arr ! (i-1, j)) >>= \x -> Just (x + 1)
                                                 else Nothing
                                         cs = [c1, c2, c3, c4] 
                                         cs'= map (fromMaybe 0) . filter (/= Nothing) $ cs
                                     in  if null cs' then Nothing else (Just . minimum $ cs')
      b1 = length s1
      b2 = length s2
      bounds = ((0, 0), (b1, b2))
      arr = listArray bounds [go i j | i <- [0..b1], j <- [0..b2]] 
  in  go (length s1in) (length s2in)

solveProblem :: Problem -> Result
solveProblem pb = findResult (pb !! 0) (pb !! 1)


