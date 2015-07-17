-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- Project Euler: Problem 5
ans5 :: Integer -> Integer
ans5 num = head. dropWhile (\n -> not . and . map (\x -> (n `mod` x == 0)) $ [num, (num-1)..1]) $ [num, (num+1)..]

main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
  mapM_ (putStrLn . show) $ map ans5 ns
  
