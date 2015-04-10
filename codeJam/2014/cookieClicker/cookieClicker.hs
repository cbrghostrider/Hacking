import System.Environment (getArgs)
import Data.Ord
import Data.List

-- values of C, F, X
type Problem = (Double, Double, Double)

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

writeOutput :: [Double] -> [String]
writeOutput = writeOutput' 1
  where writeOutput' _ [] = []
        writeOutput' n (x:xs) = ("Case #" ++ (show n) ++ ": " ++ (show x)) : writeOutput' (n+1) xs

farmBuyTimes :: Int -> Problem -> Double
farmBuyTimes n pb@(c, f, _) = sum . map (\m -> (c / (2 + m*f))) . take n $ [0, 1..]

timeToWin' :: Problem -> Int -> Double
timeToWin' pb@(c, f, x) n = farmBuyTimes n pb + (x / (2.0 + (fromIntegral n) *f))

-- given min so far, and candidate times, pick best
pickBest :: Double -> [Double] -> Double
pickBest t [] = t
pickBest t (x:xs) = if x >= t then t else pickBest x xs

timeToWin :: Problem -> Double
timeToWin pb = pickBest (head choices) (tail choices)
  where choices = map (timeToWin' pb) $ [0, 1..]

processInput :: String -> String
processInput = unlines . writeOutput . map timeToWin . map ((\[c, f, x] -> (c, f, x)) . map read . words) . tail . lines 

