-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List

processMessage :: String -> String
processMessage [] = []
processMessage ms = 
  let (os, n, c) = foldl' (\acc@(prevLs, num, ch) newch -> 
                                if newch == ch then (prevLs, num + 1, ch) else ((ch, num):prevLs, 1, newch)) 
                          ([], 1, head ms) 
                          (tail ms)
  in  concat . map (\(c, n) -> if n == 1 then c:[] else c:(show n)) . reverse $ ((c, n) : os)

main :: IO ()
main = do
  ip <- getLine
  putStrLn $ processMessage ip
