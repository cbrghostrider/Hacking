-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

-- Even though this algorithm is O(n), it is currently timing out on some large inputs!
-- It is functionally correct however, and passes fine for many smaller inputs.
import Data.Ratio
import Data.List

type Accum = (Int, Int) -- (number of 1s in window, total accumulated combos)

foldFunc :: [Char] -> Int -> Accum -> Int -> Accum
foldFunc ss k (nOnesWindow, accumCombos) newInd = 
  let droppedInd     = newInd - (k+1)
      onesWindow     = if (ss!!droppedInd) == '1' then nOnesWindow - 1       else nOnesWindow
      newOnesWindow  = if (ss!!newInd)     == '1' then onesWindow + 1        else onesWindow 
      addCombos      = if (ss!!newInd)     == '1' then newOnesWindow * 2 - 1 else 0
  in  (newOnesWindow, accumCombos + addCombos)

computeProbability :: String -> Int -> Int -> Ratio Int
computeProbability ss n k = 
  let num1sFstkp1= length . filter (== '1') . take (k + 1) $ ss ++ (repeat '0')
      initCombos = num1sFstkp1 ^ 2
      restCombos = snd . foldl' (foldFunc ss k) (num1sFstkp1, 0) $ drop (k+1) [0..(length ss - 1)]
      nume       = if length ss <= (k+1) then initCombos else initCombos + restCombos
      deno       = (length ss) ^ 2
  in (nume % deno)

runTests :: Int -> IO ()
runTests 0 = return ()
runTests nt = do
  nkstr <- getLine
  ss    <- getLine
  let [n, k] = map read . words $ nkstr
  let rat    = computeProbability ss n k
  putStrLn $ (show . numerator $ rat) ++ "/" ++ (show . denominator $ rat)
  runTests (nt-1)

main :: IO ()
main = do
  tcstr <- getLine
  runTests (read tcstr)
