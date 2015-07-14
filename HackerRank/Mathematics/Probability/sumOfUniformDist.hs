-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Ratio

-- the sum of two uniform continuous distributions is a symmetric triangular distribution
-- In particular, for [0, A], [0, B] intervals, this is an isosceles trapezoid
-- with the two triangles at distance A from the ends, the middle (B-A) and height (1/B) 
-- the various probabilities now are simply areas under the curves

-- assumes a < b
computeProbability :: Integer -> Integer -> Integer -> Rational
computeProbability a b c
  | c > (a + b)        = 1 % 1
  | c < a              = (c * c) % (2 * a * b)
  | c == a             = a % (2 * b)
  | c < b              = (2 * c - a) % (2 * b)
  | c == b             = (2 * b - a) % (2 * b)
  | otherwise {- c>b -}= let c' = a + b - c in (2 * a * b - c' * c') % (2 * a * b)

runTests :: Int -> IO ()
runTests 0 = return ()
runTests n = do
  nstr <- getLine
  let [a, b, c] = map read . words $ nstr
  let rat = if a < b then computeProbability a b c else computeProbability b a c
  putStrLn $ (show . numerator $ rat) ++ "/" ++ (show . denominator $ rat)
  runTests (n-1)

main :: IO ()
main = do
  tcs <- getLine
  runTests (read tcs)
