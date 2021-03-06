-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import System.Environment (getArgs)

{-
main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  putStrLn (processQual ip)
-}

-- takes string made up so far for curr token
-- and unconsumed input
-- returns (string for curr token, rest of unconsumed input)
consumeLtr :: String -> String -> (String, String)
consumeLtr strSoFar [] = (strSoFar, [])
consumeLtr strSoFar (')':xs) = (strSoFar, xs)
consumeLtr strSoFar (x:xs) = consumeLtr (strSoFar ++ [x]) xs

-- takes partial output, unconsumed input, and returns full output
consumeLtrStart :: [String] -> String -> [String]
consumeLtrStart strs [] = strs
consumeLtrStart strs ('(': xs) = 
  let (myStr, restStr) = consumeLtr "" xs in consumeLtrStart (strs ++ [myStr]) restStr
consumeLtrStart strs (x:xs) = consumeLtrStart (strs ++ [[x]]) xs

bindToFunc :: String -> String -> [String]
bindToFunc ls strLhs = [strLhs ++ [l] | l <- ls]

-- converts a token to a list of possible words
convert :: String -> [String]
convert = foldl (\a str -> a >>= bindToFunc str) (return []) . consumeLtrStart [] 

-- given a dict and a list of words, lists how many are in dict
listNum :: [String] -> [String] -> Int
listNum d = length . filter (== True) . map (`elem` d) 

toOpStr :: Int -> [Int] -> [String]
toOpStr n [] = []
toOpStr n (x:xs) = ("Case #" ++ (show n) ++ ":" ++ (show x)) : toOpStr (n+1) xs

processQual :: String -> String
processQual ip = 
  let allLines = lines ip
      [l, d, n]= map read . words . head $ allLines
      dict     = take d . tail $ allLines
      checkss  = map convert . take n . drop d . tail $ allLines
      nums     = map (listNum dict) checkss
      opLines  = toOpStr 1 nums
  in  unlines opLines
      

