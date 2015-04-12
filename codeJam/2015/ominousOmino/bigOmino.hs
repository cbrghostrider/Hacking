import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe
import Data.Monoid 

-- (X, R, C) values
type Problem = (Int, Int, Int)
data Result  = GABRIEL | RICHARD deriving (Eq, Show, Read)
data Direction = North | South | East | West deriving (Eq, Show, Read)

-- top left is (0, 0)
type Coord = (Int, Int)
type Omino = [Coord]
{-
main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)
-}
writeOutput :: [Result] -> [String]
writeOutput = writeOutput' 1
  where writeOutput' _ [] = []
        writeOutput' n (r:rs) = ("Case #" ++ (show n) ++ ": " ++ (writeResult r)) : writeOutput' (n+1) rs

processInput :: String -> String
processInput = unlines . writeOutput . map solveProblem . parseProblem . tail . lines

writeResult :: Result -> String
writeResult = show

parseProblem :: [String] -> [Problem]
parseProblem = map ((\[x, r, c] -> (x, r, c)) . map read . words) 

----------------------------------------------------------------------------------------
-- these functions check if Richard can win outright
----------------------------------------------------------------------------------------
--
-- if richard chooses a long line for x
maxLengthCheck :: Problem -> Maybe Result
maxLengthCheck pb@(x, r, c) = if x > r && x > c then Just RICHARD else Nothing

-- if Richard chooses a *good* L shape
ellShapeCheck :: Problem -> Maybe Result
ellShapeCheck  pb@(x, r, c) = if x >= ((smallDim + 1) * 2) - 1 then Just RICHARD else Nothing
  where smallDim = if r < c then r else c 

-- total cells should be in multiples of x
multiplesCheck :: Problem -> Maybe Result
multiplesCheck pb@(x, r, c) = if ((r * c) `mod` x) /= 0 then Just RICHARD else Nothing

----------------------------------------------------------------------------------------
-- 
----------------------------------------------------------------------------------------

-- unchecked!
getNeighbor :: Coord -> Direction -> Coord
getNeighbor c@(cx, cy) North = (cx, cy - 1) 
getNeighbor c@(cx, cy) South = (cx, cy + 1) 
getNeighbor c@(cx, cy) East  = (cx + 1, cy) 
getNeighbor c@(cx, cy) West  = (cx - 1, cy) 

sortCoord :: Coord -> Coord -> Ordering
sortCoord c1@(c1x, c1y) c2@(c2x, c2y) = (c1x `compare` c2x) `mappend` (c1y `compare` c2y)

oneXoneOmino :: Omino
oneXoneOmino = [(0, 0)] --placed at origin

-- function to generate all next level ominos, given a partial omino
genOmino :: Int -> Omino -> [Omino]
genOmino maxDim os = 
  let lenCur = length os
      neighborsRaw = concat . map (\(c, ds) -> map (getNeighbor c) ds) . zip os $ repeat [North, South, East, West]
      neighbors = nub . filter (not . (`elem` os))
                  . filter (\(x, y) -> x >=0 && y >=0) . filter (\(x, y) -> x < maxDim && y < maxDim) 
                  $ neighborsRaw 
  in map (sortBy sortCoord . (:os)) $ neighbors

getNextOminos :: Int -> [Omino] -> [Omino]
getNextOminos maxDim os = nub $ os >>= genOmino maxDim

solveProblem :: Problem -> Result
solveProblem = undefined 
