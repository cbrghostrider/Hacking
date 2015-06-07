-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 
import Data.Ratio

type Level      = Int
type Elfishness = Rational
type Problem    = Elfishness 
type Result     = Maybe Level 

maxLevel :: Level
maxLevel = 40

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

writeOutput :: [(Int, Result)] -> [String]
writeOutput = map (\(i, r) -> ("Case #" ++ (show i) ++ ": " ++ (writeResult r)))

processInput :: String -> String
processInput = unlines . writeOutput . zip [1..] . map (solveProblem maxLevel). parseProblem . tail . lines

writeResult :: Result -> String
writeResult Nothing  = "impossible"
writeResult (Just x) = show x

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (s:ss) = (n%d) : parseProblem ss
  where n = read . takeWhile (/= '/') $ s
        d = read . tail . dropWhile (/= '/') $ s

validElfness :: Elfishness -> Bool
validElfness elf = 
  let nume = numerator   elf
      deno = denominator elf
      denomax = (2 ^ maxLevel)
  in  if denomax `mod` deno == 0 then True else False

solveProblem :: Level -> Problem -> Result
solveProblem lvl elf = 
  let nume = numerator   elf
      deno = denominator elf
      newElf = (2 * nume) % deno 
  in  if validElfness elf == False
         then Nothing
         else if lvl <= 0 
                 then Nothing 
                 else if nume * 2 >= deno 
                         then Just (maxLevel - lvl + 1 )
                         else solveProblem (lvl - 1) newElf


