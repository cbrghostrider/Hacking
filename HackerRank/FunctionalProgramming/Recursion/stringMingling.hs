merge :: String -> String -> String
merge s1 s2 = concat $ zipWith (\c1 c2 -> [c1, c2]) s1 s2

main :: IO ()
main = do
  s1 <- getLine 
  s2 <- getLine
  putStrLn $ merge s1 s2
