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

