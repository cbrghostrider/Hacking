main :: IO ()
main = do 
         numbers <- readFile "IntegerArray.txt"
	 let numList = map read $ lines $ numbers
	 let numInv = countInversions numList
	 putStr "Number of Inversions = "
	 putStrLn (show numInv)

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
  

