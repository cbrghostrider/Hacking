-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
-- 
-- This solution works, but it is EXTREMELY slow
-- This is because I am doing an exponential amount of recursion
-- I need to re-formulate this problem, in a non-exponential manner
--
-- Anyway, just including the solution for completeness. You can play around with maxLevel
-- to change the depth of recursion. Lower depth makes it quicker, but with lower accuracy, 
-- and vice versa.
-- 
-- For sample
-- 1
-- abb
--
-- w/ maxLevel = 10 we get 2.68785
-- w/ maxLevel = 15 we get 2.94176
-- w/ maxLevel = 20 we get 2.99007
-- 
-- The correct answer is 3.0
--
import Control.Monad
import Data.List
import qualified Data.Map as M
import Data.Ratio
import Data.Maybe 

-- calculate probabilities up to this level
maxLevel :: Int
maxLevel = 20

-- as per problem constraints, biggest number is 8
fact :: Int -> Int
fact 0 = 1
fact 1 = 1
fact 2 = 2
fact 3 = 6
fact 4 = 24
fact 5 = 120
fact 6 = 720
fact 7 = 5040
fact 8 = 40320

choose :: Int -> Int -> Int
choose n k  = (fact n) `div` (fact k * fact (n-k))

isPalin :: String -> Bool
isPalin ss = ss == reverse ss

getCombos :: Int -> [(Int, Int)]
getCombos 2 = [(0, 1)]
getCombos n = [(p, n-1) | p <- [0..(n-2)]] ++ getCombos (n-1)

-- creates a new string by swapping the indices indicated
createString :: String -> (Int, Int) -> String
createString ss (p, n) = (take p ss) ++ [ss !! n] ++ (take (n-p-1) . drop (p+1) $ ss) ++ [ss !! p] ++ (drop (n+1) ss)

-- how many combinations of 2swaps, from all possible 2swaps, can change this into a palindrome?
getProb :: [String] -> String -> (Double, [String])
getProb palinss str = 
  let numCombos = (length str) `choose` 2 --only 2 elems swapped at a time
      allCombos = map (createString str) $ getCombos (length str)
      numPalins = length . filter (`elem` palinss) $ allCombos
      notPalins = filter (\x -> not $ x `elem` palinss) $ allCombos
  in  ((fromIntegral numPalins) / (fromIntegral numCombos), notPalins)

-- compute the expected amount of swaps, to change this string, at this level into a palindrome
-- if this level fails, recurse beyond it
probForLevel :: [String] -> M.Map String (Double, [String]) -> Int -> Double -> String -> Double
probForLevel palinss mmap swapNo probSoFar curStr = 
  let (succProb, failstrs) = fromMaybe (0, []) $  M.lookup curStr mmap --if this swap were to succeed
      leafExpect = fromIntegral swapNo * succProb * probSoFar
      numCombos  = (length curStr) `choose` 2 --only 2 elems swapped at a time
      multProb   = probSoFar  / (fromIntegral numCombos)
      failExpect = sum $ map (probForLevel palinss mmap (swapNo + 1) multProb) failstrs
  in  if swapNo == maxLevel then 0 else leafExpect + failExpect

expectedSwaps :: String -> Double
expectedSwaps []  = 0 --empty string
expectedSwaps [_] = 0 --or one length string dont need any swaps
expectedSwaps str = 
  let allss   = permutations str
      palinss = filter isPalin allss
      mymap   = M.empty 
      finmap  = foldl' (\accmap st -> M.insert st (getProb palinss st) accmap) mymap $ allss
  in  if isPalin str then 0 else probForLevel palinss finmap 1 1 str


main :: IO ()
main = do
  ip <- getContents
  let ss = tail . lines $ ip
  let expects = map expectedSwaps ss
  mapM_ (putStrLn) $ map show expects

