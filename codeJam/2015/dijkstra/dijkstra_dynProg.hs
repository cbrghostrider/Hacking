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

type Problem = [Quat]
type Result  = Bool 
type QuatCh  = Char
data Sign    = Plus | Minus deriving (Eq)
type Quat    = (Sign, QuatCh)
type Index   = Int
type Cand    = (Index, Index) -- a candidate string (from index, to index) amongst trio to try

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
writeResult True  = "YES"
writeResult False = "NO"

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (ns:ss:sss) = (map parseQuat . concat . replicate num $ ss) : parseProblem sss
  where num = last . map read . words $ ns

quatChMult :: (QuatCh, QuatCh) -> Quat
quatChMult ('1',  x ) = (Plus,   x)
quatChMult ( x , '1') = (Plus,   x)
quatChMult ('i', 'i') = (Minus, '1')
quatChMult ('j', 'j') = (Minus, '1')
quatChMult ('k', 'k') = (Minus, '1')
quatChMult ('i', 'j') = (Plus,  'k')
quatChMult ('j', 'i') = (Minus, 'k')
quatChMult ('j', 'k') = (Plus,  'i')
quatChMult ('k', 'j') = (Minus, 'i')
quatChMult ('k', 'i') = (Plus,  'j')
quatChMult ('i', 'k') = (Minus, 'j')
quatChMult _          = error "Unknown multiplication"

signMult :: Sign -> Sign -> Sign
signMult Plus x      = x
signMult Minus Plus  = Minus
signMult Minus Minus = Plus

qMult :: Quat -> Quat -> Quat
qMult x y =
  let sx = fst x
      sy = fst y
      (sr, cr) = quatChMult (snd x, snd y)
  in  (signMult sr (signMult sx sy) , cr)

parseQuat :: QuatCh -> Quat
parseQuat x = (Plus, x)

solveQuatStr :: Problem -> [(Cand, Cand, Cand)] -> Bool
solveQuatStr s cands = any (==True) . map solve $ cands 
  where
    go :: Index -> Index -> Quat 
    go i j 
      | j < i     = error "Something wrong in dynamic programming"
      | i == j    = s !! i  -- this is just the character
      | otherwise = let mid = i + ((j-i) `div` 2) 
                        t1 = (arr ! (i, mid)) 
                        t2 = (arr ! (mid+1, j)) 
                    in (t1 `seq` t2) `seq` qMult t1 t2
    limit  = length s - 1
    bounds = ((0, 0), (limit, limit))
    arr = listArray bounds [go si ei | si <- [0..limit], ei <- [0..limit]] 
    solve (c1, c2, c3) = let (v1, v2, v3) = (go (fst c1) (snd c1), go (fst c2) (snd c2), go (fst c3) (snd c3)) 
                         in v1 == (Plus, 'i') && v2 == (Plus, 'j') && v3 == (Plus, 'k')

solveProblem :: Problem -> Result
solveProblem s = solveQuatStr s [((0, b1), (b1+1, b2), (b2+1, (length s - 1))) | b1 <- [0..(length s - 3)], b2 <- [(b1+1)..(length s - 2)] ]


