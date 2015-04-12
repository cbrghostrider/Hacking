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

-- checks that for all indices from i = 0 to i = (length p - 3)
-- which multiplication of [0, i] reduces to "i"
-- returns those candidate indices
-- all indices are 0 indexed
getS1Ends :: Problem -> [Index]
getS1Ends p = 
  let start = 0
      end   = length p - 3
      str   = take (end + 1) p
      fres  = foldl' (\(amult, als) (s, i) -> let nmult = qMult amult s 
                                              in  if nmult == (Plus, 'i') then (nmult, i:als) else (nmult, als)) 
                     ((Plus, '1'), []) $ zip str [start..end]
  in  reverse . snd $ fres

getS3Starts :: Problem -> [Index]
getS3Starts p =  
  let start = 2
      end   = length p - 1
      str   = drop (start) p
      fres  = foldr (\(s, i) (amult, als) -> let nmult = qMult s amult
                                             in  if nmult == (Plus, 'k') then (nmult, i:als) else (nmult, als)) 
                    ((Plus, '1'), []) $ zip str [start..end]
  in  snd $ fres

-- evaluates the multiplication for the middle string
evaluateMiddle :: Problem -> Index -> Index -> Quat
evaluateMiddle p sm em = 
  let str = take (em - sm + 1) . drop sm $ p
      mult = foldr (\s acc -> qMult s acc) (Plus, '1') str
  in  if null str then error "Off by 1 error!" else mult

solveProblem :: Problem -> Result
solveProblem s = 
  let indS1Ends   = getS1Ends   s   -- indices from [0, to any in indS1Ends] evaluate to i
      indS3Starts = getS3Starts s   -- indices from [any in indS3Starts to, (length p - 1)] evaluate to k
      midIndices  = [(ef + 1, sl - 1) | ef <- indS1Ends, sl <- indS3Starts, sl > ef] 
      wholeString = (== (Minus, '1')) . foldr (\s acc -> qMult s acc) (Plus, '1') $ s  -- is whole string "ijk" which is (-1)
      s1EarliestEnd = head . sort $ indS1Ends
      s3LatestStart = last . sort $ indS3Starts
  in  if null indS1Ends || null indS3Starts
         then False
         else if s1EarliestEnd > s3LatestStart
                 then False
                 else if wholeString == False 
                         then False
                         else True


