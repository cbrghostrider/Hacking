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

keyMap :: [(Char, String)]
keyMap = [('a', "2"), ('b', "22"), ('c', "222"),
          ('d', "3"), ('e', "33"), ('f', "333"),
          ('g', "4"), ('h', "44"), ('i', "444"), 
          ('j', "5"), ('k', "55"), ('l', "555"), 
          ('m', "6"), ('n', "66"), ('o', "666"), 
          ('p', "7"), ('q', "77"), ('r', "777"), ('s', "7777"),
          ('t', "8"), ('u', "88"), ('v', "888"), 
          ('w', "9"), ('x', "99"), ('y', "999"), ('z', "9999"),
          (' ', "0"), ('#', " ")]

getXlation :: Char -> String
getXlation c = snd . head . filter ((==c) . fst) $ keyMap

shouldInsertPause :: Char -> Char -> Bool
shouldInsertPause c1 c2 = (head . getXlation $ c1) == (head . getXlation $ c2)

-- takes the original message, and inserts pause characters in between 
-- every immediately repeating letter
-- e.g. abbcb => ab#bcb
insertPauses :: String -> String
insertPauses = fst . foldl (\(opStr, lastChr) chr -> if shouldInsertPause lastChr chr then ((opStr ++ ['#', chr]), chr) else ((opStr ++ [chr]), chr)) ([], '#')

-- takes an input (with pauses) and converts to output
keyXlation :: String -> String
keyXlation [] = []
keyXlation (x:xs) = (getXlation x) ++ keyXlation xs

processInput :: String -> String 
processInput = unlines . map (\(n, str) -> "Case #" ++ (show n) ++ ": " ++ str) . zip [1..] . map (keyXlation . insertPauses) . tail . lines 


