-- assuming no repeats in array as per problem statement

type PivotFunc = [Int] -> Int

pivotFirst :: PivotFunc
pivotFirst = head

pivotLast :: PivotFunc
pivotLast = last

pivotMedian :: PivotFunc
pivotMedian ls = 
  let
    len = length ls
    fElem = head ls
    lElem = last ls
    mElem = if odd (length ls) then ls !! (len `div` 2) else ls !! ((len `div` 2) - 1)
  in if len < 2 then error "Found list of length less than 2"
                else chooseMedian fElem lElem mElem

chooseMedian :: Int -> Int -> Int -> Int
chooseMedian a b c 
 | (a <= b && b <= c) || (c <= b && b <= a) = b
 | (b <= c && c <= a) || (a <= c && c <= b) = c
 | otherwise      			    = a


-- the base quicksort algorithm, which sorts using given function to choose pivot
-- takes as input the list to be sorted, and returns the (#comparisons, sorted list)
quickSort' :: PivotFunc -> [Int] -> (Int, [Int])
quickSort' _ []  = (0, [])
quickSort' _ [x] = (0, [x])
quickSort' pf ls = 
  let pivot = pf ls
      lesserPart  = [x | x <- ls, x < pivot]
      greaterPart = [x | x <- ls, x > pivot]
      (nrl, sortLesser)  = quickSort' pf lesserPart
      (nrg, sortGreater) = quickSort' pf greaterPart
  in  (length ls - 1 + nrl + nrg, sortLesser ++ [pivot] ++ sortGreater)

main :: IO ()
main = do
  	 numbers <- readFile "tc100r.txt" --"rand.txt" --"IntegerArray.txt" --"QuickSort.txt"
	 let (fc, sort1) = quickSort' pivotFirst  $ (map read) . lines $ numbers
	 let (lc, sort2) = quickSort' pivotLast   $ (map read) . lines $ numbers
	 let (mc, sort3) = quickSort' pivotMedian $ (map read) . lines $ numbers
	 putStrLn . concat $ ["The comparisons using first  are: ", show fc, "\n"]
	 putStrLn . concat $ ["The comparisons using last   are: ", show lc, "\n"]
	 putStrLn . concat $ ["The comparisons using median are: ", show mc, "\n"]
	 mapM_ (\x -> putStrLn$ show x) sort3


