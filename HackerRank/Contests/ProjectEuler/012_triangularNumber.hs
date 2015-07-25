-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

factors' :: Integer -> [Integer]
factors' n = map fst . filter (\ (x, y) -> y == 0) . zip [1..n] . map (n `mod`) $ [1..n']
  where n' = (1 + (truncate.sqrt.fromIntegral $ n))::Integer

factors :: Integer -> [Integer]
factors n = nub (factList ++ modList)
  where factList = factors' n
        modList = map (n `div` ) factList
        
triNums :: [Integer]
triNums = scanl1 (+) [1..] 

ans12 :: Int -> Integer
ans12 query = fst . head . dropWhile (\(t, l) -> l <=query ). zip triNums . map length . map factors $ triNums

main :: IO ()
main = do
  ip <- getContents
  let ns = map read . tail . lines $ ip
      anss = map ans12 ns
  mapM_ (putStrLn . show) anss
