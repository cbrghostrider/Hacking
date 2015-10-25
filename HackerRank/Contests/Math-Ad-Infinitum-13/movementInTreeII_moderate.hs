-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

-- Note that the Haskell version is slow, because of use of Integer (some tests TLE)
-- The cpp version has AC

c_MODNUM :: Integer
c_MODNUM = 1000000007

computeUnr :: Bool -> Integer -> Integer -> Integer -> Integer
computeUnr bl d k h = 
  let n     = (k - h - 1) `div` 2
      dmult = if bl == True then d else 1
      f     = d * d
      term  = dmult * (((f ^ (n+1)) - 1) `div` (f - 1))
  in  (term `mod` c_MODNUM)

computeUnrOdd  = computeUnr False
computeUnrEven = computeUnr True

unreacheable' :: Integer -> Integer -> Integer -> Integer
unreacheable' d k h 
  | ((k - h) `mod` 2) == 0 = computeUnrEven d k h
  | otherwise              = computeUnrOdd d k h

unreacheable :: Integer -> Integer -> Integer -> Integer
unreacheable d k h = if h > k then 0 else unreacheable' d k h

computeAns :: Integer -> Integer -> Integer -> Integer
computeAns d k h = 
  let dt'   = ((d ^ (k+1))-1) `div` (d-1)
      dt    = dt' `mod` c_MODNUM
      delta = unreacheable d k h 
  in  (dt - delta + c_MODNUM) `mod` c_MODNUM

runTests :: Int -> IO ()
runTests 0 = return ()
runTests tc = do
  dkhstr <- getLine
  let [d, k, h] = map read . words $ dkhstr
  let ans = computeAns d k h
  putStrLn $ show ans
  runTests (tc-1)

main :: IO ()
main = do
  tcstr <- getLine
  let tc = read tcstr
  runTests tc
