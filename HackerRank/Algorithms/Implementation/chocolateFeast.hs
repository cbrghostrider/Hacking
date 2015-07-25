-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

chocRecurse :: Int -> Int -> Int
chocRecurse haveWraps costWraps 
  | haveWraps < costWraps = 0
  | otherwise             = 
      let newChocs = haveWraps `div` costWraps 
          leftWraps = haveWraps `mod` costWraps
      in  newChocs + chocRecurse (newChocs + leftWraps) costWraps

numChocolates :: Int -> Int -> Int -> Int
numChocolates money cost cwraps = chocDirect + chocRecursive
  where chocDirect    = money `div` cost
        chocRecursive = chocRecurse chocDirect cwraps

main :: IO ()
main = do
  ip <- getContents
  let nss  = map (map read . words) . tail . lines $ ip
      anss = map (\[m, c, w] -> numChocolates m c w) nss 
  mapM_ (putStrLn . show) anss

