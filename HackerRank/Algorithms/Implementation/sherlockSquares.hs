-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

c_LIMIT :: Int
c_LIMIT = 10^9

sqrIntegers :: [Int]
sqrIntegers = takeWhile (<= c_LIMIT) [(x^2) | x <- [1..]] 

numSquares :: Int -> Int -> Int
numSquares a b = length . takeWhile (<=b) . dropWhile (< a) $ sqrIntegers

solveProblem :: [Int] -> Int
solveProblem ns = numSquares (head ns) (last ns)

main :: IO ()
main = do
  ip <- getContents
  let numss = map (map read . words) . tail . lines $ ip
      anss  = map solveProblem numss
  mapM_ (putStrLn . show) anss
