-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Ratio

solveProblem :: Int -> Int -> (Int, Ratio Int)
solveProblem r s = 
  let fullCirclesTrav  = r `div` s 
      partCirclesTrav = r `mod` s
  in  if partCirclesTrav * 4 <= s
                 then (r, (r `mod` s) % s)
                 else ((fullCirclesTrav + 1)*s, 0%1)

runTests :: Int -> IO ()
runTests 0 = return ()
runTests n = do
  rsstr <- getLine
  let [r, s] = map read . words $ rsstr
  let (ansa, ansb) = solveProblem r s
  putStrLn $ (show ansa) ++ " " ++ (show . numerator $ ansb) ++ "/" ++ (show . denominator $ ansb)
  runTests (n-1)

main :: IO ()
main = do
  tcstr <- getLine
  runTests (read tcstr)
