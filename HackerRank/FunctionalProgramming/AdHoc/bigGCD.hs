import Data.List

bigGCD :: [Integer] ->[Integer] -> Integer
bigGCD ns ms = gcd (reduce ns) (reduce ms)
  where reduce = foldl' (*) 1

main :: IO ()
main = do 
  nstr  <- getLine
  nsstr <- getLine
  mstr  <- getLine
  msstr <- getLine
  let ans = (`mod` (10^9 + 7)) $ bigGCD (map read . words $ nsstr) (map read . words $ msstr)
  putStrLn $ show ans
