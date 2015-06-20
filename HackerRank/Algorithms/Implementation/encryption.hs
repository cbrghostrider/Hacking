-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- some quick haskell code, looks a bit spaghetti

import Data.List
import Data.Ord

encryption :: [String]-> [String]
encryption wds = 
  let nlets    = sum . map length $ wds
      rowlim   = floor . sqrt . fromIntegral $ nlets
      collim   = ceiling  . sqrt . fromIntegral $ nlets
      cols     = [1..collim]
      rcs      = [ (r, c) | c <- cols, let r = ceiling $ (fromIntegral nlets / fromIntegral c),
                                       c>=r, (r*c)>=nlets, r>= rowlim]
      (sr, sc) = fst. head . sortBy (comparing snd) . zip rcs . map (\(p, q) -> p*q) $ rcs
      str      = concat wds
      wdlines  = unfoldr (\st -> if null st then Nothing else if length st < sr then Just ((take sr$ st ++ repeat '#'), "") else Just (take sc st, drop sc st) ) str
      wdlines' = transpose wdlines
  in  map (filter (/= '#')) wdlines'
      

main :: IO ()
main = interact $ unlines . (\x->[x]) . unwords . encryption . words
