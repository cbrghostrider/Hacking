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
