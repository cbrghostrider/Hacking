
-- main = main1_4

(^%^) = \a b -> a + b

main1_4 = interact tpText

tpText :: String -> String
tpText = unlines . transposeMatrix . convertToRectMatrix . lines

convertToRectMatrix :: [[Char]] -> [[Char]]
convertToRectMatrix iss = scanr1 (\cl _ -> cl ++ ((take (maxLen - length cl)) $ repeat ' ')) $ iss
  where maxLen = maximum . (map length) $ iss

transposeMatrix :: [[a]] -> [[a]]
transposeMatrix iss 
  | all null iss    = [] 
  | otherwise       = (map head iss) : (transposeMatrix . map tail $ iss)


