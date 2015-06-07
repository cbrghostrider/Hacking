-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
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

sortFlips :: [Bit] -> [Bit] -> Ordering
sortFlips [] [] = EQ
sortFlips [] _  = error "unequal lengths"
sortFlips _  [] = error "unequal lengths"
sortFlips (l:ls) (r:rs)
  | numTrue (l:ls) < numTrue (r:rs) = LT
  | numTrue (l:ls) > numTrue (r:rs) = GT
  | l < r  = LT
  | l > r  = GT
  | l == r = sortFlips ls rs
    where numTrue = length . filter (== One)

xorBits :: Bit -> Bit -> Bit
xorBits Zero Zero = Zero
xorBits Zero One  = One
xorBits One Zero  = One
xorBits One One   = Zero

xorFlows :: Flow -> Flow -> Flow
xorFlows f1 f2 = map (\(b1, b2) -> b1 `xorBits` b2) $ zip f1 f2

-- takes the first device flow, and a list of outlet flows
-- returns a list of flip strings, that can cause flows to match
-- sorts the candidates before returning, in terms of number of least # Ones
genFlowCandidates :: Flow -> [Flow] -> [Flow]
genFlowCandidates seq = sortBy (sortFlips) . map (xorFlows seq)

solveProblem :: Problem -> Result
solveProblem pb@(n, l, oss, dss) = 
  let flipCands = genFlowCandidates (head dss) oss
      osss'     = map sort . map (\fc -> map (xorFlows fc) oss) $ flipCands
      dss'      = sort dss
      matches   = filter ((==True) . snd) . zip flipCands . map (== dss') $ osss'
  in  if null matches 
         then Nothing
         else Just (length . filter (== One) . fst . head $ matches)


