-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

foldFuncPress :: (Integer, [Bool]) -> Integer -> (Integer, [Bool])
foldFuncPress (bigProd, bvs) myval = (newProd, (firstOne:bvs))
  where newProd = bigProd `div` myval
        firstOne= ((bigProd `div` myval) `mod` myval) == 0

foldFuncProds :: (Integer, [Integer]) -> (Integer, Bool) -> (Integer, [Integer])
foldFuncProds (intProd, ps) (myval, mybool) = (newprod, (newprod:ps))
  where newprod = if mybool then myval * intProd else intProd

getProdPresenceList :: [Integer] -> ([Bool], [Integer])
getProdPresenceList ns = 
  let bigProd = product ns
      press   = reverse . snd . foldl' foldFuncPress (bigProd, []) $ ns
      prods   = reverse . snd . foldl' foldFuncProds (1, []) $ zip ns press
  in  (press, prods)

runQueries :: Int -> ([Bool], [Integer]) -> [Integer] -> IO ()
runQueries 0 _ _ = return ()
runQueries q pps aps = do
  lrstr <- getLine
  let [l, r] = map read . words $ lrstr
      (li, ri) = (l-1, r-1)
      sval1 = (!! ri) . snd $ pps
      fval1 = if li == 0 then 1 else ((!! (li-1)) . snd $ pps)
      yval  = (sval1 `div` fval1) 
      sval2 = (!! ri) $ aps
      fval2 = if li == 0 then 1 else ((!! (li-1))  $ aps)
      xval  = (sval2 `div` fval2) 
      zval  = fval1
      gval  = gcd xval zval
      dval  = (xval `div` gval) `div` yval
      fans  = (gval * yval) `div` dval
  putStrLn $ show $ fans `mod` 3
  runQueries (q-1) pps aps

main :: IO ()
main = do 
  nqstr <- getLine
  nsstr <- getLine
  let [n, q] = map read . words $ nqstr
      ns = map read . words $ nsstr
      pps = getProdPresenceList ns
      allProds = reverse . snd $ foldl' (\(acc, ls) n -> (acc*n, ((acc*n):ls))) (1, []) ns
  runQueries q pps allProds
