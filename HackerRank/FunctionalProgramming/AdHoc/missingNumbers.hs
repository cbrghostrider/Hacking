-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List 
import Data.HashTable.IO as HT
import Control.Monad as CM

type HashTable k v = HT.BasicHashTable k v

processNums :: HashTable Int Int -> [Int] -> IO ()
processNums htablens ns = do
  forM_ ns $ \n -> do
      check <- HT.lookup htablens (fromIntegral n)
      if check == Nothing
          then do
              HT.insert htablens (fromIntegral n) 1
          else do
              let Just val = check
              HT.insert htablens (fromIntegral n) (val+1)

checkFreq :: HashTable Int Int -> (Int, Int) -> IO ([Int])
checkFreq htablens (km, vm) = do
  check <- HT.lookup htablens (fromIntegral km)
  if check == Nothing
      then return (replicate vm km)
      else do
          let Just val = check
          if val >= vm
              then return ([])
              else return (replicate (vm-val) km)

solveProblem :: [Int] -> [Int] -> IO [Int]
solveProblem ns ms = do
  htablens <- HT.new 
  htablems <- HT.new 
  processNums htablens ns
  processNums htablems ms
  kvms     <- HT.toList htablems
  CM.foldM (\accls (k, v) -> (checkFreq htablens (k, v)) >>= \news -> return (accls ++ news)) [] . 
                map (\(k, v) -> (fromIntegral k, fromIntegral v)) $ kvms

main :: IO ()
main = do
  nstr  <- getLine
  nsstr <- getLine
  mstr  <- getLine
  msstr <- getLine
  anss  <- solveProblem (map read . words $ nsstr) (map read . words $ msstr) 
  putStrLn $ unwords . map show . nub . sort $ anss
  
