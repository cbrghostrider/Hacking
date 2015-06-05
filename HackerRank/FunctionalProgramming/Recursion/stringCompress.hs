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
