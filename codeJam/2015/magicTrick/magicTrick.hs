import System.Environment (getArgs)
import Data.Ord
import Data.List

type Problem = (Int, [[Int]], Int, [[Int]])

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

writeOutput'' :: Int -> Maybe [Int] -> String
writeOutput'' n Nothing    = ("Case #" ++ (show n) ++ ": " ++ "Volunteer cheated!") 
writeOutput'' n (Just [x]) = ("Case #" ++ (show n) ++ ": " ++ (show x))
writeOutput'' n _          = ("Case #" ++ (show n) ++ ": " ++ "Bad magician!")

writeOutput :: [Maybe [Int]] -> [String]
writeOutput = writeOutput' . zip [1..]
  where writeOutput' [] = []
        writeOutput' ((n, x):xs) = (writeOutput'' n x) : writeOutput' xs

readInput :: [String] -> [Problem]
readInput [] = []
readInput (n:a1:a2:a3:a4:m:b1:b2:b3:b4:xs) = 
  let n'  = read n
      nss = [(map read . words $ a1), (map read. words $ a2), (map read . words $ a3), (map read . words $ a4)]
      m'  = read m
      mss = [(map read . words $ b1), (map read. words $ b2), (map read . words $ b3), (map read . words $ b4)]
  in  (n', nss, m', mss) : readInput xs
readInput _ = error "Malformed input!"

solveProblem :: Problem -> Maybe [Int]
solveProblem (n, nss, m, mss) = 
  let rn = nss !! (n-1)
      rm = mss !! (m-1)
      isecNM = rn `intersect` rm
  in  if null isecNM then Nothing else Just (isecNM)

processInput :: String -> String 
processInput = unlines . writeOutput . map solveProblem . readInput . tail . lines


