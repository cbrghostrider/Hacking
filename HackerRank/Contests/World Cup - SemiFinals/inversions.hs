-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List
import Data.Ord

main :: IO ()
main = do 
     ip <- getContents
     let ns      = map read . words . last . lines  $ ip
     let sizenum = length ns
     let origInv = countInversions ns
     let indices = invIndices sizenum
     let cands   = sortBy (comparing snd) . dropWhile ((> origInv) . (snd)) . zip indices . map (countInversions . manipList ns) $ indices
     let chosen  = fst . head $ cands
     putStrLn $ if null cands then "Cool Array" else ((show . (+1) . fst $ chosen) ++ " " ++ (show . (+1) . snd $ chosen))
     
manipList :: [Int] -> (Int, Int) -> [Int]
manipList ns (i, j) = (take i ns) ++ [secondNum] ++ ( drop (i+1) . take j $ ns) ++ [firstNum] ++ (drop (j+1) ns)
  where firstNum  = ns !! i
        secondNum = ns !! j

invIndices :: Int -> [(Int, Int)]
invIndices n = [(i, j) | i <- [0..(n-1)], j <- [0..(n-1)], i<j]

countInversions :: [Int] -> Int
countInversions ns = (\(_, inv, _) -> inv) $ countInversions' (fromIntegral $ length ns, ns)

-- takes (len, list) -> (len, #inv, sorted-list)
countInversions' :: (Int, [Int]) -> (Int, Int, [Int])
countInversions' (_, []) 	= (0, 0, [])
countInversions' (_, [n]) 	= (1, 0, [n])
countInversions' (totLen, ns)	= 
  let half = totLen `div` 2
      ps = take half ns
      qs = drop half ns
      (lp, pn, sps) = countInversions' (half, ps)
      (lq, qn, sqs) = countInversions' (totLen - half, qs)
      (mn, sms) = sortAndCountSplitInversions (lp, sps) (lq, sqs)
  in  (totLen, pn + qn + mn, sms)

-- takes 2 x (len-list, unsorted list) -> (num-split-inv, sorted-merged-list)
sortAndCountSplitInversions :: (Int, [Int]) -> (Int, [Int]) -> (Int, [Int])
sortAndCountSplitInversions (_, []) (_, rs) = (0, rs)
sortAndCountSplitInversions (_, ls) (_, []) = (0, ls)
sortAndCountSplitInversions (ll, (l:ls)) (lr, (r:rs)) 
  | l < r  = (a      , l:as) 
  | l > r  = (b + ll, r:bs)
  | l == r = (c      , l:r:cs)
    where
      (a, as) = sortAndCountSplitInversions (ll - 1, ls) (lr, (r:rs))
      (b, bs) = sortAndCountSplitInversions (ll, (l:ls)) (lr - 1, rs)
      (c, cs) = sortAndCountSplitInversions (ll - 1, ls) (lr - 1, rs)
