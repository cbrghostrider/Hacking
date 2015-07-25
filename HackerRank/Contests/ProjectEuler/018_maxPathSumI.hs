-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
processAll :: [[Int]] -> Int
processAll = head. head . scanr processRow (repeat 0)

processRow :: [Int] -> [Int] -> [Int]
processRow row lowerLvl = foldr (\(n, val) partRow -> (maxChoice val (lowerLvl !! n) (lowerLvl !! (n+1))) : partRow) [] (zip [0..] row)
  where
    maxChoice v l r = if (v + l) < (v + r) then (v + r) else (v + l)

main18 :: [[Int]] -> IO ()
main18 nss = putStrLn $ show . processAll $ nss

runTest :: Int -> [String] -> IO ()
runTest 0 _ = return ()
runTest n ss = do
  let nlines = read . head $ ss
      nss    = map (map read . words) . take nlines . tail $ ss
  main18 nss
  runTest (n-1) (drop (nlines + 1) ss)

main :: IO ()
main = do
  alllines <- getContents
  let tc       = read . head . lines $ alllines
      allInput = tail . lines $ alllines
  runTest tc allInput
