charToInt :: Char -> Int
charToInt '0' = 0
charToInt '1' = 1
charToInt '2' = 2
charToInt '3' = 3
charToInt '4' = 4
charToInt '5' = 5
charToInt '6' = 6
charToInt '7' = 7
charToInt '8' = 8
charToInt '9' = 9

superDigit :: String -> String
superDigit [n] = [n]
superDigit ns  = superDigit . show . sum . map charToInt $ ns

solveProblem :: String -> String -> String
solveProblem n k = let sdn = superDigit n in superDigit . concat . take (read k) . repeat $ sdn

main :: IO ()
main = do
  ip <- getLine
  let [n, k] = words $ ip
  putStrLn $ solveProblem n k
