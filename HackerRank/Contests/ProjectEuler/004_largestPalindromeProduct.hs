-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

isPalindrome :: (Eq a) => [a] -> Bool
isPalindrome xs = xs == reverse xs

-- Project Euler: Problem 4
ans4 :: Integer -> Integer
ans4 n = head . dropWhile (not.isPalindrome.show) . filter (<n) . reverse . sort $ [x * y | x <- listNums, y <- listNums]
  where listNums = [999, 998..100]

main :: IO ()
main = do 
  ip <- getContents
  let ns = map read . tail . lines $ ip
  mapM_ (putStrLn . show) $ map ans4 ns
