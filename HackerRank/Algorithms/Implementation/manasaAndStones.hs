-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

solveProblem :: Int -> Int -> Int -> [Int]
solveProblem 1 _ _ = [0]
solveProblem n a b = sort . nub $ map (\(x, y) -> a*x + b*y) [(x, y) | x <- [0..(n-1)], y <- [0..(n-1)], x+y == (n-1)] 

runTests :: Int -> IO ()
runTests 0 = return ()
runTests tc = do
  nstr <- getLine
  astr <- getLine
  bstr <- getLine
  let (n, a, b) = (read nstr, read astr, read bstr)
  putStrLn $ unwords . map show $ solveProblem n a b
  runTests (tc-1)

main :: IO ()
main = do 
  tcstr <- getLine
  runTests (read tcstr)
