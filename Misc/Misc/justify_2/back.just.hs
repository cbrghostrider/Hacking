import System.Environment (getArgs)

-- a function that does some type of alignment on a list of words
type AlignFunc = (Int -> Int -> [String] -> [String]) 
type AlignType = String			

main :: IO ()
main = do
  args <- getArgs
  case args of 
      [inputFile, alignStr, alignVal] -> do
        input <- readFile inputFile
	writeFile (alignStr++"."++alignVal++"."++inputFile) (alignAllLines alignStr (read alignVal) input)
      _ -> error "Usage: ./justify inputFile alignType indentVal"

alignAllLines :: AlignType -> Int -> String -> String
alignAllLines d n = unlines.(map unwords).(alignAllLines' d n).concat.(map words).lines

alignAllLines' :: AlignType -> Int -> [String] -> [[String]]
alignAllLines' d n 
  | d == "left" = align alignLeft n 
  | d == "right" = align alignRight n
  | d == "center" = align alignCenter n
  | d == "justify" = align (\ n c str -> str) n
  | otherwise = error "Unknown alignment type for program (left/right/center/justify allowed)"
    where
      alignLeft n spaceConsumed words = init words ++ [(last words) ++ (take (n - spaceConsumed) (repeat ' '))]
      alignRight n spaceConsumed = reverse.(map reverse).(alignLeft n spaceConsumed).(map reverse).reverse
      alignCenter n spaceConsumed = (alignRight n spaceConsumed).(alignLeft (spaceConsumed + ((n-spaceConsumed) `div` 2)) spaceConsumed)

align :: AlignFunc -> Int -> [String] -> [[String]]
align _ _ [] = []
align f n allWords = (f n spaceConsumed wordsOnLine) : (align f n remainingWords)
  where
    (numFit, spaceConsumed) = numWordsToFit n allWords
    (wordsOnLine, remainingWords) = (take numFit allWords, drop numFit allWords)

--takes an align amount, and list of words, and returns pair of
--(num of words that will fit within the align amount, amount of space those words will take (with 1 space between them))
numWordsToFit :: Int -> [String] -> (Int, Int)
numWordsToFit n [] = (0, 0)
numWordsToFit n wordList = (length candidateCumLengths, last candidateCumLengths)
  where
    cumulativeLengths = map (\x -> x - 1) $ tail $ foldl (\listCumLen newLen -> listCumLen ++ [1 + newLen + last listCumLen]) [0] $ map length wordList
    candidateCumLengths = takeWhile (\x-> x <=n) cumulativeLengths




