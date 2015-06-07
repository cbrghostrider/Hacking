-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- This solution got accepted, after I turned a linear search into binary search
import Data.List

-- computes the fewest mangoes consumed when number of friends in the party are fixed to f
mangoesConsumed :: [Int] -> [Int] -> Int -> Int
mangoesConsumed as hs f = sum . take f . sort . map (\(a, h) -> a + (f-1)*h) $ zip as hs

binarySearchFriends :: [Int] -> [Int] -> [Int] -> (Int, Int) -> Int
binarySearchFriends [n, m] as hs (loi, hii) 
  | loi == hii     = mangoesConsumed as hs loi
  | loi == hii - 1 = 
    let loms   = mangoesConsumed as hs loi
        hims   = mangoesConsumed as hs hii
    in  if hims <= m then hii else loi
  | otherwise      = 
    let mid    = (loi + hii) `div` 2 
        midms  = mangoesConsumed as hs mid
    in if midms == m 
          then mid 
          else if midms < m
                  then binarySearchFriends [n, m] as hs (mid, hii)
                  else binarySearchFriends [n, m] as hs (loi, mid)

-- try picking # of friends from 0, 1, 2, ... using binary search, until constraint is broken
solveProblem :: [Int] -> [Int] -> [Int] -> Int
solveProblem [n, m] as hs = binarySearchFriends [n, m] as hs (0, n) 

main :: IO ()
main = do 
  nmstr <- getLine
  asstr <- getLine
  hsstr <- getLine
  putStrLn $ show $ solveProblem (map read . words $ nmstr) (map read . words $ asstr) (map read . words $ hsstr)


