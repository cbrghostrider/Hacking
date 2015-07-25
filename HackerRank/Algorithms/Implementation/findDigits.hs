-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Char

solveProblem :: Integer -> Int
solveProblem num = length . filter ((== 0) . (num `mod`)) . map (fromIntegral . digitToInt) . filter (/= '0') . show $ num

main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
  let anss = map solveProblem ns
  mapM_ (putStrLn . show) anss
