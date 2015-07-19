-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- 
-- Naive algorithm for now
--
findSubStr :: String -> String -> Bool
findSubStr ns hs
  | length ns > length hs       = False
  | (take (length ns) hs) == ns = True
  | otherwise                   = findSubStr ns (drop 1 hs)

runTestCase :: Int -> IO ()
runTestCase 0 = return ()
runTestCase n = do
  haystack <- getLine
  needle <- getLine
  let ans = findSubStr needle haystack
  putStrLn $ if ans == True then "YES" else "NO"
  runTestCase (n-1)

main :: IO () 
main = do 
  tc <- getLine
  runTestCase (read tc)

