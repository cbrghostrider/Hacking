-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

-- same O(n) algorithm as before, but using arrays instead of lists, and it runs lightning fast!

import Data.Ratio
import Data.List
import Data.Array

type Accum = (Int, Int) -- (number of 1s in window, total accumulated combos)

foldFunc :: Array Int Char -> Int -> Accum -> Int -> Accum
foldFunc arr k (nOnesWindow, accumCombos) newInd = 
  let droppedInd     = newInd - (k+1)
      onesWindow     = if (arr!droppedInd) == '1' then nOnesWindow - 1       else nOnesWindow
      newOnesWindow  = if (arr!newInd)     == '1' then onesWindow + 1        else onesWindow 
      addCombos      = if (arr!newInd)     == '1' then newOnesWindow * 2 - 1 else 0
  in  (newOnesWindow, accumCombos + addCombos)

computeProbability :: Array Int Char -> String -> Int -> Int -> Ratio Int
computeProbability arr ss n k = 
  let num1sFstkp1= length . filter (== '1') . take (k + 1) $ ss ++ (repeat '0')
      initCombos = num1sFstkp1 ^ 2
      restCombos = snd . foldl' (foldFunc arr k) (num1sFstkp1, 0) $ drop (k+1) [0..(length ss - 1)]
      nume       = if length ss <= (k+1) then initCombos else initCombos + restCombos
      deno       = (length ss) ^ 2
  in (nume % deno)

runTests :: Int -> IO ()
runTests 0 = return ()
runTests nt = do
  nkstr <- getLine
  ss    <- getLine
  let [n, k] = map read . words $ nkstr
  let arr    = listArray (0, length ss -1) ss
  let rat    = computeProbability arr ss n k
  putStrLn $ (show . numerator $ rat) ++ "/" ++ (show . denominator $ rat)
  runTests (nt-1)

main :: IO ()
main = do
  tcstr <- getLine
  runTests (read tcstr)
