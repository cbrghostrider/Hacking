-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import System.Environment (getArgs)
import Data.Maybe

main :: IO ()
main = do
  [file]  <- getArgs
  ip <- readFile file
  writeFile ((takeWhile (/= '.') file) ++ ".out" ) (processInput ip)

processInput' :: String -> [String]
processInput' = map unwords . map reverse . map words . tail . lines 

processInput :: String -> String
processInput = unlines . map (\(n, ln) -> "Case #" ++ (show n) ++ ": " ++ ln) . zip [1..] . processInput'

