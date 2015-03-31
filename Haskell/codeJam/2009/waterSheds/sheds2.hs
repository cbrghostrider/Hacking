import System.Environment (getArgs)
import Data.Maybe
import Data.Monoid
import Data.Ord
import Data.List
import Debug.Trace 

--{-
main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)
---}
data Direction = North | West | East | South deriving (Show, Read, Eq, Ord)
type Altitude  = Int
type Coord     = (Int, Int)               -- top left is (0, 0)
type AltMap    = [[Altitude]]             -- an array of altitudes
type Map       = (Int, Int, AltMap)       -- map contains nRows, nCols, and array of altitudes
type FlowMap   = [[Maybe Direction]]      -- shows what direction a particular cell flows into
type SinkMap   = [[Coord]]                -- shows which coord is my ultimate sink
type LetterMap = [[Char]]

-- max # of rows or cols as defined in problem
c_MAXDIM :: Int
c_MAXDIM = 100

labels :: String
labels = concat . repeat $ ['a', 'b'..'z']

allCoords :: (Coord) -> [[Coord]]
allCoords (nrow, ncol) = [[(x, y) | x <- [0..(ncol-1)] ] | y <- [0..(nrow-1)]]

-- reads a single map from input lines, and returns it along with unconsumed input lines
readInput' :: [String] -> (Map, [String])
readInput' (x:xs) = 
  let [nr, nc] = (map read . words $ x)
      restOfIp = drop nr xs
      myIp     = take nr xs
  in  ((nr, nc, (map (map read . words) myIp)), restOfIp)
readInput' _ = error "Unexpected end of input"

readInput :: [String] -> [Map]
readInput [] = [] 
readInput ip = let (m1, rofip) = readInput' ip in m1 : readInput rofip

getElem :: [[a]] -> Coord -> a
getElem m (x, y) = (m !! y) !! x

-- does not check bounds
getCellInDir :: Direction -> Coord -> Coord
getCellInDir North (x, y) = (x, y-1)
getCellInDir West  (x, y) = (x-1, y)
getCellInDir East  (x, y) = (x+1, y)
getCellInDir South (x, y) = (x, y+1)

-- given bounds nr and nc, and a coordinate, 
-- gives its (possibly 4 or less) neighbors
getNeighbors :: (Int, Int) -> Coord -> [(Direction, Coord)]
getNeighbors (nrow, ncol) c@(x, y) = 
  let nc = getCellInDir North c 
      wc = getCellInDir West  c
      ec = getCellInDir East  c
      sc = getCellInDir South c
  in  filter (\(_, (x', y')) -> x' >= 0 && x' < ncol && y' >= 0 && y' < nrow) $ [(North, nc), (West, wc), (East, ec), (South, sc)]

sortOnAlt :: (Direction, Altitude) -> (Direction, Altitude) -> Ordering
sortOnAlt c1@(dc1, ac1) c2@(dc2, ac2) = (ac1 `compare` ac2) `mappend` (dc1 `compare` dc2)

-- returns Nothing if this is a sink coord
-- else returns the direction we flow into
getFlowDirForCoord :: (Int, Int) -> AltMap -> Coord -> Maybe Direction
getFlowDirForCoord (nrow, ncol) am c = 
  let neighDirAlts = sortBy sortOnAlt . map (\(cd, cc) -> (cd, getElem am cc)) . getNeighbors (nrow, ncol) $ c
      neighDirAlt  = head neighDirAlts
      myAlt        = getElem am c
  in  if null neighDirAlts || myAlt <= snd neighDirAlt then Nothing else Just (fst neighDirAlt)

getSinkCell :: FlowMap -> Coord -> Coord
getSinkCell fm myc = 
  let myFlowDir  = getElem fm myc
      myFlowDir' = fromMaybe North myFlowDir
  in  if myFlowDir == Nothing
         then myc  -- I am my own sink
         else getSinkCell fm (getCellInDir myFlowDir' myc)

sinkToLetterMap :: [(Char, Coord)] -> String -> [Coord] -> [(Char, Coord)]
sinkToLetterMap ms ls []     = ms
sinkToLetterMap ms ls (s:sm) = 
  if s `elem` (map snd ms) 
     then sinkToLetterMap ms ls sm
     else sinkToLetterMap ((head ls, s) : ms) (tail ls) sm

getSinkToLetter :: [(Char, Coord)] -> Coord -> Char
getSinkToLetter slmap c = fst . head . filter ((==c) . snd) $ slmap 

xlateLetterMap :: Int -> LetterMap -> String
xlateLetterMap n lm = unlines $ ("Case #" ++ (show n) ++ ":") : (map (init . concat) . map (map (:" ")) $ lm)

createLetterMap :: (Int, Int) -> SinkMap -> LetterMap
createLetterMap limits sm = map (map (getSinkToLetter slmap)) $ sm
  where slmap = sinkToLetterMap [] labels (concat sm)

createSinkMap :: (Int, Int) -> FlowMap -> SinkMap
createSinkMap limits fm = map (map (getSinkCell fm)) . allCoords $ limits

createFlowMap :: (Int, Int) -> AltMap -> FlowMap 
createFlowMap limits am = map (map (getFlowDirForCoord limits am)) . allCoords $ limits

processMap :: Int -> Map -> String
processMap mapNum m@(nrow, ncol, am) = xlateLetterMap mapNum . createLetterMap (nrow, ncol) . createSinkMap (nrow, ncol) . createFlowMap (nrow, ncol) $ am

processInput :: String -> String 
processInput = concat . map (\(n, m) -> processMap n m) . zip [1..] . readInput . tail . lines


