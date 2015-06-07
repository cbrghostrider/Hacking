-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List 
import Data.HashTable.IO as HT
import Control.Monad

type HashTable k v = HT.BasicHashTable k v

createHashTable ::IO (HashTable Int Int)
createHashTable = do
  ht <- HT.new
  return ht
     
solveProblem :: String -> String -> IO [Int]
solveProblem ips nsstr = do
  htable <- createHashTable
  let [n, k] = map read . words $ ips
  let ns     = map read . words $ nsstr
  forM_ ns $ \n -> do
      check <- HT.lookup htable n
      if check == Nothing
          then do
              HT.insert htable n 1
          else do
              let Just val = check
              HT.insert htable n (val+1)
  kvs <- HT.toList htable
  let fns = map fst . filter ((>=k) . snd) $ kvs
  let os  = filter (`elem` fns)  $ ns
  if null os then return [-1] else return (nub os)


runTestCase :: Int -> IO ()
runTestCase 0 = return ()
runTestCase n = do
  ips <- getLine
  ns  <- getLine
  ans <- solveProblem ips ns
  putStrLn $ unwords . map show $ ans
  runTestCase (n-1)

main :: IO ()
main = do
  ntc <- getLine
  runTestCase (read ntc)
