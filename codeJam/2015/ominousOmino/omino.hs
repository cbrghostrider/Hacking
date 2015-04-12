import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 

-- (X, R, C) values
type Problem = (Int, Int, Int)
data Result  = GABRIEL | RICHARD deriving (Eq, Show, Read)

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

-- for a 2 omino, richard will win for maxLengthCheck or for multiplesCheck
solveProblem pb@(2, r, c) = if mxLenChk /= Nothing || multChk /= Nothing then RICHARD else GABRIEL
  where mxLenChk = maxLengthCheck pb
        multChk  = multiplesCheck pb

-- for a 3 omino
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
  | r <= 3 && c <= 3 = RICHARD
  | r <= 2 || c <= 2 = RICHARD
  | otherwise        = error "Shouldn't come here"

-- for everything else
solveProblem _ = error "Pathetic, worked out first 4 cases on paper! Muahahahaha!"

