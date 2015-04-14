import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 

data Bit = Zero | One deriving (Eq, Ord)
type Flow = [Bit]
type Problem = (Int, Int, [Flow], [Flow])
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
writeResult Nothing  = "NOT POSSIBLE"
writeResult (Just x) = show x

readBit :: Char -> Bit
readBit '0' = Zero
readBit '1' = One

parseProblem :: [String] -> [Problem]
parseProblem [] = []
parseProblem (nl:os:ds:ss) = ((read . head . words $ nl), (read . last . words $ nl), 
                               (map (map readBit) . words $ os), (map (map readBit) . words $ ds)) : parseProblem ss

flipBit :: Bit -> Bit
flipBit Zero = One
flipBit One  = Zero

getOutlets :: Problem -> [Flow]
getOutlets (_, _, os, _) = os

getSpecs :: Problem -> [Flow]
getSpecs (_, _, _, ds)   = ds

sortFlips :: [Bool] -> [Bool] -> Ordering
sortFlips [] [] = EQ
sortFlips [] _  = error "unequal lengths"
sortFlips _  [] = error "unequal lengths"
sortFlips (l:ls) (r:rs)
  | numTrue (l:ls) < numTrue (r:rs) = LT
  | numTrue (l:ls) > numTrue (r:rs) = GT
  | l < r  = LT
  | l > r  = GT
  | l == r = sortFlips ls rs
    where numTrue = length . filter (== True)

-- takes L, and gives an ordered list of candidates to try
-- list is size L, where each index is no-flip or flip
getCandidates :: Int -> [[Bool]]
getCandidates 0   = []
getCandidates ell =  sortBy (sortFlips) . foldl' (>>=) (return []) . take ell . repeat $ (\ls -> [(False : ls), (True : ls)] )

flipFlow :: [Bool] -> Flow -> Flow
flipFlow bs fs = map (\(b, f) -> if b then flipBit f else f) $ zip bs fs

solveProblem :: Problem -> Result
solveProblem pb@(n, l, os, ds) = if null options then Nothing else Just value
  where ds'     = sort ds
        cands   = getCandidates l
        options = filter ((== ds') . snd) . zip cands . map (sort) . map (\cf -> map (flipFlow cf) os) $ cands
        value   = length . filter (== True) . fst . head $ options
      


