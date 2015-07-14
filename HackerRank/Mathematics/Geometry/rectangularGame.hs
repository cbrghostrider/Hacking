-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

solveProblem :: [[Int]] -> Int
solveProblem  = (\[vx, vy] -> vx * vy) . foldl1 (\[accx, accy] [x, y] -> [min accx x, min accy y]) 

main :: IO ()
main = do
  ip <- getContents
  let nmss = map (map read . words) . tail . lines $ ip
      ans  = solveProblem nmss
  putStrLn . show $ ans
