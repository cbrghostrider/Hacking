-- Sourabh S Joshi
-- https://code.google.com/codejam/contest/32016/dashboard#s=p0
-- Greedy algorithm for solving problem is below

import System.Environment (getArgs)
import Data.List (sort)

type Vector  = [Int]            -- represents the x and y indices each
type Problem = (Vector, Vector) -- two vectors per problem

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

genOutput :: [Int] -> [String]
genOutput = genOutput' 1
  where genOutput' _ [] = []
        genOutput' n (x:xs) = ("Case #" ++ (show n) ++ ": " ++ (show x)) : genOutput' (n+1) xs

sign :: [Int] -> Int
sign [] = 0 -- if arrays has all zeros or nothing, sign really does not matter
sign (x:xs)
  | signum x == 0 = sign xs
  | otherwise = signum x

solveProblem :: Problem -> Int
solveProblem (v1, v2) = 
  let sv1          = reverse . sort $ v1
      sv2          = reverse . sort $ v2
      (nv1, pv1)   = ((reverse . filter (<0) $ sv1), (filter (>=0) $ sv1))
      (nv2, pv2)   = ((reverse . filter (<0) $ sv2), (filter (>=0) $ sv2))
      mult_nv1_pv2 = zipWith (*) nv1 pv2
      mult_pv1_nv2 = zipWith (*) pv1 nv2
      part1        = sum mult_nv1_pv2 + sum mult_pv1_nv2
      rem_v1       = drop (length mult_nv1_pv2) nv1 ++ drop (length mult_pv1_nv2) pv1
      rem_v2       = drop (length mult_nv1_pv2) pv2 ++ drop (length mult_pv1_nv2) nv2
      part2        = 
        if sign rem_v1 == sign rem_v2 -- both remainders same sign
           then sum $ zipWith (*) rem_v1 (reverse rem_v2)
           else sum $ zipWith (*) rem_v1 rem_v2
  in  if length rem_v1 /= length rem_v2
         then error "Something went wrong"
         else if null rem_v1 && null rem_v2
                 then part1
                 else part1 + part2

parseProblem :: Int -> String -> String -> Problem
parseProblem n v1 v2 = ((map read . words $ v1), (map read . words $ v2))

parseInput :: [String] -> [Problem]
parseInput (n:v1:v2:xs) = (parseProblem (read n) v1 v2) : parseInput xs
parseInput _ = []

processInput :: String -> String
processInput = unlines . genOutput . map solveProblem . parseInput . tail . lines


