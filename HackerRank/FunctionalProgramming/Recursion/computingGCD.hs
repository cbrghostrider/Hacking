module Main where

gcd' :: Integral a => a -> a -> a
gcd' n m 
  | n == 0 || m == 0 = 1
  | n == m           = n
  | n < m            = gcd' (m-n) n 
  | n > m            = gcd' (n-m) m

main = do
  input <- getLine
  print . uncurry gcd' . listToTuple . convertToInt . words $ input
 where
  listToTuple (x:xs:_) = (x,xs)
  convertToInt = map (read :: String -> Int)
