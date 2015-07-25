-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.Char

piDigs :: String
piDigs = "31415926535897932384626433833"

letters :: String
letters = "abcdefghijklmnopqrstuvwxyz"

getNumStr :: String -> String
getNumStr ss =  
  let seqs = map length . words . filter ( `elem` (' ':(letters ++ (map toUpper letters)))) $ ss
      slen = length seqs
      ssstr = concat . map show $ seqs
      psstr = take slen piDigs
  in  if psstr == ssstr 
         then "It's a pi song."
         else "It's not a pi song."

main :: IO ()
main = do
  ip <- getContents
  let songs = tail . lines $ ip
      nss   = map getNumStr songs
  mapM_ putStrLn nss
