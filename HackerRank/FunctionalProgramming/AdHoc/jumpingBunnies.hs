-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

lcmlist :: [Int] -> Int
lcmlist = foldl1' (\alcm num -> lcm alcm num)

main :: IO ()
main = do
  _     <- getLine
  nsstr <- getLine
  putStrLn $ show $ lcmlist (map read . words $ nsstr)
