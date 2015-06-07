-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Control.Monad

solveProblem' :: [Int] -> Int -> Int -> Int
solveProblem'  _  0 n = 1
solveProblem' [1] x n = if x == 1 then 1 else 0
solveProblem' ns x n  = if check > x then notIncThis else notIncThis + incThis 
  where
    num        = last ns
    check      = num ^ n
    notIncThis = solveProblem' (init ns) x n
    incThis    = solveProblem' (init ns) (x - check) n

solveProblem :: Int -> Int -> Int 
solveProblem x n = 
  let lastN = floor . sqrt . fromIntegral $ x
  in  solveProblem' [1..lastN] x n
      
main :: IO ()
main = do
  ip <- getContents
  let [x, n] = map read . lines $ ip
  putStrLn $ show $ solveProblem x n 
