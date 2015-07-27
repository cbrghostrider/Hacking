-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

main :: IO ()
main = do
  ip <- getContents
  let ts = map read . words . last . lines $ ip
      ans = snd . foldl' (\a@(freeTill, spent) wt -> 
                             if wt <= freeTill then (freeTill, spent) else (wt + 4, spent + 1) )
                         (-1, 0) $ sort ts
  putStrLn $ show ans
