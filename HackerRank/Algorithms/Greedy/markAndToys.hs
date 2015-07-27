-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

main :: IO ()
main = do
  nkstr <- getLine
  psstr <- getLine
  let [n, k] = map read . words $ nkstr
      ps     = map read . words $ psstr
      ans    = snd . foldl' 
                     (\acc@(money, sofar) price -> if price <= money then (money-price, sofar+1) else (money, sofar) ) 
                     (k, 0) . sort $ ps
  putStrLn $ show ans
