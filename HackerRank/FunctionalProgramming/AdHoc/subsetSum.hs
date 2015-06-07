-- currently timing out on big inputs even though Im using binary search!
-- not sure why... I tried to use deepseq to force eval of the cumulative sum list, but it didn't make a difference. 
-- Need to optimize from 16 sec to < 5 sec. Open to suggestions!
import Data.List
import Control.DeepSeq

binSearchMinSSS' :: Int -> [Int] -> (Int, Int) -> Int
binSearchMinSSS' s ss (lo, hi) 
  | lo == hi     = lo  -- size of the subarray is (index+1)
  | lo == hi - 1 = if (ss !! lo) > s then lo else hi 
  | otherwise    = 
    let mid = (hi+lo) `div` 2
    in  if (ss !! mid) == s 
           then mid
           else if (ss !! mid) < s 
                   then binSearchMinSSS' s ss (mid, hi)
                   else binSearchMinSSS' s ss (lo, mid)

binSearchMinSSS :: Int -> [Int] -> (Int, Int) -> Int
binSearchMinSSS s ss (lo, hi) = 
  let ans = binSearchMinSSS' s ss (lo, hi) 
  in  if (ss !! ans) < s then -1 else 1 + ans

runTestCases :: Int -> [Int] -> IO ()
runTestCases 0 _ = return ()
runTestCases n ss = do
  sstr <- getLine
  putStrLn $ show $ binSearchMinSSS (read sstr) ss (0, length ss - 1)
  runTestCases (n-1) ss

main :: IO ()
main = do
  nstr  <- getLine
  asstr <- getLine
  tcstr <- getLine
  let ss = reverse . sort $ (map read . words $ asstr)
      cands = reverse . foldl' (\accs n -> (head accs + n):accs) [head ss] $ tail ss
  runTestCases (read tcstr) (cands `deepseq` cands)
