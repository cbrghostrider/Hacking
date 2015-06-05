prepareOutput :: String -> String -> String -> String
prepareOutput ps s1 s2 = unlines [(show . length $ ps) ++ " " ++ (reverse ps), 
                                  (show . length $ s1) ++ " " ++ s1, 
                                  (show . length $ s2) ++ " " ++ s2]

processCompression :: String -> String -> String -> String
processCompression prefix [] s2           = prepareOutput prefix [] s2
processCompression prefix s1 []           = prepareOutput prefix s1 []
processCompression prefix (c1:s1) (c2:s2) = if c1 /= c2 then prepareOutput prefix (c1:s1) (c2:s2)
                                                        else processCompression (c1:prefix) s1 s2

main :: IO ()
main = do
  s1 <- getLine
  s2 <- getLine
  putStrLn $ processCompression [] s1 s2
