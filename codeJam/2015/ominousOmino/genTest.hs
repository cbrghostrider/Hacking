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

