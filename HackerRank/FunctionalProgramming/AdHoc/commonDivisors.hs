-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
solveProblem :: [Int] -> Int
solveProblem [m, l] = length . filter (\k -> ((m `mod` k) == 0) && ((l `mod` k) == 0)) $ [1..(gcd m l)]
  
runTestCases :: Int -> IO ()
runTestCases 0 = return ()
runTestCases n = do
  nsstr <- getLine
  putStrLn $ show . solveProblem $ (map read . words $ nsstr)
  runTestCases (n-1)
  
main :: IO ()
main = do
  tcstr <- getLine
  runTestCases (read tcstr)
