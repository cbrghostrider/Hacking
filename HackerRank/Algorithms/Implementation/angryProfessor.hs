-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

computeAns :: Int -> [Int] -> Bool
computeAns k ns = (>= k) . length . filter (<=0) $ ns

runTests :: Int -> IO ()
runTests 0 = return ()
runTests t = do
  nkstr <- getLine
  nsstr <- getLine
  let [n, k] = map read . words $ nkstr
  let ns     = map read . words $ nsstr
  let ans    = computeAns k ns
  putStrLn $ if ans == True then "NO" else "YES"
  runTests (t-1)

main :: IO ()
main = do
  tcstr <- getLine
  runTests (read tcstr)
