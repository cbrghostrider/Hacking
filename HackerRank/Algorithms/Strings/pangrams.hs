-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Char (toLower)
import Data.List (sort, nub)

isPangram :: String -> Bool
isPangram = (== letters) . nub . sort . filter (`elem` letters) .map toLower
  where letters = "abcdefghijklmnopqrstuvwxyz"

main :: IO ()
main = do
  ip <- getContents
  let result = isPangram ip
  putStrLn $ if result == True then "pangram" else "not pangram"
