import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 
import Data.Monoid

-- (X, R, C) values
type Problem = (Int, Int, Int)
data Result  = GABRIEL | RICHARD deriving (Eq, Show, Read)

data Direction = North | South | East | West deriving (Eq, Show, Read)
type Coord = (Int, Int) -- top left is (0, 0)
type Omino = [Coord]

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

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

-- these functions check if Richard can win outright
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

-- for a 1 omino, richard cant ever win
solveProblem :: Problem -> Result
solveProblem pb@(1, _, _) = GABRIEL

solveProblem pb@(2, r, c) = if mxLenChk /= Nothing || multChk /= Nothing || ellChk /= Nothing 
                               then RICHARD else GABRIEL
  where mxLenChk = maxLengthCheck pb
        multChk  = multiplesCheck pb
        ellChk   = ellShapeCheck pb

solveProblem pb@(3, r, c) = if mxLenChk /= Nothing || ellChk /= Nothing || multChk /= Nothing
                               then RICHARD else GABRIEL
  where mxLenChk = maxLengthCheck pb
        ellChk   = ellShapeCheck pb
        multChk  = multiplesCheck pb

-- for a 4 omino
-- a I x J grid where ( 1 <= I,J <= 3 )  will always fail the maxLengthCheck - Richard wins
-- a I x J grid where (I <= 2 or J <= 2) will always fail, because Richard can choose the T or S omino
-- a 4x3 or 3x4 grid, Gabriel can win all cases, no matter what richard chooses (checked on paper)
-- a 4x4 case is a case of 3x4 or 4x3 with a single 4x1 omino tacked along at the new spot - Gabriel always wins
solveProblem pb@(4, 3, 4) = GABRIEL 
solveProblem pb@(4, 4, 3) = GABRIEL
solveProblem pb@(4, 4, 4) = GABRIEL
solveProblem pb@(4, r, c) 
  | r <= 3 && c <= 3             = RICHARD
  | r <= 2 || c <= 2             = RICHARD
  | maxLengthCheck pb /= Nothing = RICHARD
  | multiplesCheck pb /= Nothing = RICHARD
  | ellShapeCheck  pb /= Nothing = RICHARD
  | otherwise                    = GABRIEL

--other than the constraints from above as usual (3 checks), 
--this case is "small enough" that I can work out the unique ominos
--I think there are 12 shapes:
--        (line, small-L, big-L, C, S, W, Plus, number-6-ish, number-4-ish, plus 3 irregular)
--I picked the smallest rectangular shape that does not get filtered out by conditions below
--this is r=5, c=3
--all shapes except W can be filled in to create a full-block of 5x3 on paper
--for W, the next one to try is either 10x3 or 5x4
--the (5x4, W) case can be filled by 1 more W and 2 big-L
--the (10x3, W) case can be filled by (T, 6, W, 6, T)
--therefore, I only special case where r==3 or c==3 and the other (r or c) is 5 (or from 5 to 9)
--for those cases, RICHARD wins, else GABRIEL wins
solveProblem pb@(5, r, c)  
  | maxLengthCheck pb /= Nothing = RICHARD
  | multiplesCheck pb /= Nothing = RICHARD
  | ellShapeCheck  pb /= Nothing = RICHARD
  | c == 3 && r >= 5 && r <= 9   = RICHARD  -- pick W shape to win
  | r == 3 && c >= 5 && c <= 9   = RICHARD  -- pick W shape to win
  | otherwise                    = GABRIEL

-- honestly, I have no idea how I can solve the case for 6
-- there are too many ominos to consider, so I wont even try
-- instead let me see if I can construct counter examples for small sized grids
-- Pick smallest case that filters through constraints below:
--   (6 r/c x 3 c/r)  ?? I can construct a jesus-cross shaped omino, and
--                     it doesnt look like this grid can be filled in   
--   (12r/c x 3 c/r)  ?? for any case where c==3 or r==3, use jesus cross
--                     one   side of partition has free squares N*3 + 2 (where N is a natural number)
--                     other side of partition has free squares N*3 + 4 (where N is a natural number)
--                     i.e. neither side has multiple of 6, so this case richard can always win
--                     he divided the grid into two unfilled halves, neither of which can be filled properly
-- I'm not even going to try to guess the rest of the (r x c) grids
-- in fact for all others guess gabriel... im sick of this case 6 
solveProblem pb@(6, r, c)  
  | maxLengthCheck pb /= Nothing = RICHARD
  | multiplesCheck pb /= Nothing = RICHARD
  | ellShapeCheck  pb /= Nothing = RICHARD
  | c == 3 || r == 3             = RICHARD
  | otherwise                    = GABRIEL --guess! 

-- any problem for X >= 7, Richard will always win, 
-- because he can create a donut shaped omino, 
-- with a hole in the center!
-- To let the refreshment through... wat
solveProblem _ = RICHARD

--------------------------------------------------------------------------------
--       Function to generate candidates that are valid
--       Load in GHCI interpreter and play around
--------------------------------------------------------------------------------
limitR = 20
limitC = 20

-- given an X value, generates a candidate list of the form where each element of list is
-- (x, row, col) choice for this
genCandidates :: Int -> [(Int, Int, Int)]
genCandidates ominoVal = 
  let probsRaw = [(ominoVal, x, y) | x <- [1..20] , y <- [1..20]]
      probs = filter ((==Nothing) . multiplesCheck) . filter ((== Nothing) . maxLengthCheck) . filter ((==Nothing) . ellShapeCheck) $ probsRaw
  in  probs


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
growOmino :: Int -> Int -> Omino -> [Omino]
growOmino maxx maxy os = 
  let lenCur = length os
      neighborsRaw = concat . map (\(c, ds) -> map (getNeighbor c) ds) . zip os $ repeat [North, South, East, West]
      neighbors = nub . filter (not . (`elem` os))
                  . filter (\(x, y) -> x >=0 && y >=0) . filter (\(x, y) -> x < maxx && y < maxy) 
                  $ neighborsRaw 
  in map (sortBy sortCoord . (:os)) $ neighbors

-- get all ominos of size maxDim that start at coordinates given
getOminos :: Problem -> [Coord] -> [Omino]
getOminos pb@(x, r, c) origins = 
  let flist = take (x - 1) $ repeat (growOmino c r)
      candidates org = foldl' (>>=) [[org]] flist
  in  nub . concat . map candidates $ origins

