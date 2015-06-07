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

type Problem = [String]
type Result  = Maybe Int
type Rle     = [(Int, Char)] -- Run length encoding to represent each string

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

convertRle :: String -> Rle
convertRle [] = []
convertRle ls = foldr (\cl ((num, letter):rles) -> if cl == letter then ((num+1, letter):rles) else ((1, cl):(num, letter):rles)) ([(1, l)]) $ ls'
  where l   = last ls
        ls' = init ls

possibleConv :: Rle -> Rle -> Bool
possibleConv rle1 rle2 = if length rle1 /= length rle2 then False else all (==True) . map (\((_, ch1), (_, ch2)) -> if ch1 == ch2 then True else False) $ zip rle1 rle2

impossible :: [Rle] -> Bool
impossible [] = True
impossible rles = any (==False) . map (possibleConv (head rles)) $ tail rles

getSubStr :: (Rle -> a) -> [Rle] -> [a]
getSubStr _ [] = []
getSubStr f rles = if all (==[]) rles then [] else map f rles

findConvCount :: [Rle] -> Int
findConvCount [] = 0
findConvCount rles = 
  let hrle  = sortBy (comparing fst) . getSubStr head $ rles
      trles = getSubStr tail rles
      mid   = ((length hrle) `div` 2) 
      median= if length hrle `mod` 2 == 1 then (fst $ hrle !! mid) else ((fst $ hrle !! (mid-1)) + (fst $ hrle !! (mid))) `div` 2
      sumofabsdiffs = sum . map (abs . (subtract median) . fst) $ hrle
  in sumofabsdiffs + findConvCount trles

minConversions :: [Rle] -> Result
minConversions rles = if null rles || impossible rles then Nothing else Just (findConvCount rles)

solveProblem :: Problem -> Result
solveProblem = minConversions . map convertRle 


