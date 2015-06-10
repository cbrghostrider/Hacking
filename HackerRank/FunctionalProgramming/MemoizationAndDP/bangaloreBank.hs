-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Array
import Data.List
import Data.Char

-- this is one entry in the cache, it is a list of (left position, right position, mintimesofar)
-- it is a list because all min time candidates are saved (and some more, see big note below)
type CacheVal = [(Int, Int, Int)]

initialPositions :: CacheVal
initialPositions = [(l, r, 0) | l <- [1..10], r <- [l..10]]

expandLocation :: Int -> (Int, Int, Int) -> CacheVal
expandLocation dig (l, r, v) = 
  let lcost = abs $ l - dig       
      rcost = abs $ r - dig
      lcand = (dig, r, v+lcost+1)  -- lcost to move + 1 cost to press key
      rcand = (l, dig, v+rcost+1)  -- rcost to move + 1 cost to press key
  in  lcand : rcand : [] 

-- similar to the dice problem, we need to keep more than just the minval candidates because:
-- consider iteration (n-1):
-- say you have 2 potential candidates with following locations and minval (l, r, val)
-- (1, 1, x) and (1, 0, x+8)
-- usually we would only keep the first candidate
-- however, if the next digit is 0, now the new candidates would become
-- (1, 0, x+9+1) --> moves 9 positions right and press key; and;
-- (1, 0, x+8+1) --> no moves, and just press key
-- so by not keeping the second candidate in iteration (n-1), we get the wrong result
-- so how many such candidates should we keep? 
-- note that the maximum distance that can be moved is 9 (from one extreme to the other)
-- therefore we can keep all candidates that have difference <=9 from minimum 
enlistBestCandidates :: CacheVal -> Int -> CacheVal
enlistBestCandidates inCands dig = 
  let newPosCosts = concat . map (expandLocation dig) $ inCands
      minVal      = minimum . map (\(_, _, v) -> v) $ newPosCosts
  in  nub . filter (\(_, _, v) -> abs (v - minVal) <= 9) $ newPosCosts

bangaloreBank :: [Int] -> Array Int CacheVal
bangaloreBank ns = cache 
  where
    go k 
      | k == 0    = initialPositions
      | otherwise = enlistBestCandidates (cache ! (k-1)) (ns !! (k-1)) 

    cache :: Array Int CacheVal
    cache = listArray (0, length ns) [go i | i <- [0..(length ns)]]
                  
-- renames the keyboard from [1, 2, 3, .... 9, 0] to [1, 2, 3..., 9, 10]
renameNumbers :: [String] -> [Int]
renameNumbers [] = []
renameNumbers (n:ns) = (renameDigit $ read n) : renameNumbers ns
  where renameDigit :: Int -> Int
        renameDigit k = if k == 0 then 10 else k

main :: IO ()
main = do 
  ip <- getContents
  let ns    = renameNumbers . words . last . lines $ ip
      cache = bangaloreBank ns 
  putStrLn $ show . minimum . map (\(_, _, v) -> v) $ (cache ! (length ns))

