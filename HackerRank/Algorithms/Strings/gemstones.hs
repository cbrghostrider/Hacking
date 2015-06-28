-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------

isGemElem :: [String] -> Char -> Bool
isGemElem ss ch = all (==True) . map (ch `elem`) $ ss

numGemElements :: [String] -> Int
numGemElements ss = length . filter (isGemElem ss) $ letters
  where letters = "abcdefghijklmnopqrstuvwxyz"

main :: IO ()
main = do
  ip <- getContents
  let rs = tail . lines $ ip
  putStrLn . show $ numGemElements rs
