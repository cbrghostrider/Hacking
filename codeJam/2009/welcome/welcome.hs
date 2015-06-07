-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- Woot! Haskell Lazy Dynamic Programming!!
-- Google Code Jam 2009: Qualification Round: Problem C
-- Welcome to Code Jam
-- Problem Statement: http://code.google.com/codejam/contest/90101/dashboard#s=p2&a=2

import System.Environment (getArgs)
import Data.Array

source :: String 
source = "welcome to code jam"

main = do
  [ipfile] <- getArgs
  ip <- readFile ipfile
  writeFile ((takeWhile (/= '.') ipfile) ++ ".out") (processInput ip)

outputString :: [String] -> [String]
outputString = outputString' 1
  where outputString' n []     = []
        outputString' n (x:xs) = ("Case #" ++ (show n) ++ ": " ++ x) : outputString' (n+1) xs

integerToText :: Integer -> String
integerToText = reverse . take 4 . reverse . ("0000" ++) . show

subsequence :: String -> String -> Integer
subsequence ss ws = go (length ws) (length ss) -- note go indices are flipped; w first then s
  where
    go :: Int -> Int -> Integer
    go wi si
      | si == 0 = 1 
      | wi == 0 = 0
      | otherwise = 
          if ss !! (si - 1) == ws !! (wi - 1)  -- if last letters are same
             then ds ! ((wi-1), (si-1)) + ds ! ((wi- 1), si)
             else ds ! ((wi-1), si)
    (bw, bs) = (length ws, length ss)
    bounds = ((0, 0), (bw, bs))  
    ds = listArray bounds [go wi si| wi <- [0..bw], si <- [0..bs]] 

processInput :: String -> String
processInput = unlines . outputString . map (integerToText . subsequence source) . tail . lines

