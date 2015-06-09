-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
--
-- Current solution falls *just* short of the allotted 5 second for test case #17, 
-- which is a degenerate case of horribly overlapping, and short passwords.
-- All other tests pass (17/18)
import Data.Array

-- each "index" has this list, which if not null means string from 0..index is a password combination
-- For each such combination, Int is the set of combinations from 0..intval-1 and intval..index is a valid password itself
type PWCache = [(Int, String)]

passwordCracker :: String -> [String] -> Array Int PWCache
passwordCracker teststr ps = cache
  where
    go n
      | n == 0    = let word = [teststr !! 0] in if word `elem` ps then [(0, word)] else []
      | otherwise = constructCacheEntry n
    constructCacheEntry :: Int -> PWCache
    constructCacheEntry k = 
      let testns = [1..k]
          wholeWord = (take (k+1) teststr)
          restwords = map (\i -> (drop i . take (k+1) $ teststr)) $ [1..k]
          pwcaches  = filter ( \ (i, word) -> (word `elem` ps) && (not . null $ (cache ! (i-1)))) $ zip [1..k] restwords
      in  if wholeWord `elem` ps then (0, wholeWord) : pwcaches else pwcaches
    cache = listArray (0, length teststr-1) [go k | k <- [0..(length teststr - 1)]] 

getValidCombo :: Array Int PWCache -> Int -> [String]
getValidCombo cache n = 
  let c     = cache ! n
      entry = head c
  in  if null c then [] else if fst entry == 0 then [snd entry] else (snd entry) : getValidCombo cache (fst entry - 1)

runTestCases :: Int -> IO ()
runTestCases 0 = return ()
runTestCases n = do
  _       <- getLine
  psstrs  <- getLine
  teststr <- getLine
  let cache = passwordCracker teststr (words psstrs)
  let strs  = reverse $ getValidCombo cache (length teststr - 1)
  putStrLn $ if null strs || null teststr then "WRONG PASSWORD" else unwords strs
  runTestCases (n-1)

main :: IO ()
main = do
  tcstr <- getLine
  runTestCases (read tcstr)
