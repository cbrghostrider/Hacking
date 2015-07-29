-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

foldfunc :: [Int] -> Int -> Int -> Int -> Int
foldfunc ss k accunf ind = 
  let newunf = (ss !! (ind+k-1)) - (ss !! (ind))
  in  if newunf < accunf then newunf else accunf

minUnfairness :: [Int] -> Int -> Int
minUnfairness ns k = 
  let ss = sort ns
      inds = reverse . drop (k-1) . reverse . take (length ss) $ [0..] 
      unf  = (ss !! (k-1)) - (ss !! 0)
      minchoice = foldl' (foldfunc ss k) unf $ tail inds
  in  minchoice
  
main :: IO ()
main = do
  ip <- getContents
  let k  = read . head . tail . lines $ ip
      ns = map read . tail . tail . lines $ ip
      unf = minUnfairness ns k
  putStrLn $ show unf
