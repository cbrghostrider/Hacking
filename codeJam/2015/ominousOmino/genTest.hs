-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import System.Environment (getArgs)
import Data.Ord
import Data.List
import Data.Maybe 
import Data.Monoid

main :: IO ()
main = do
  [file]  <- getArgs
  writeFile (file) (tests)

tests :: String 
tests = unlines $ [(testsOminoN 5), (testsOminoN 6)]

testsOminoN :: Int -> String
testsOminoN x = unlines . map unwords . map (\(x, r, c) -> [show x, show r, show c]) 
                    $ [(x, r, c) | r <- [1..20], c <- [1..20]]

