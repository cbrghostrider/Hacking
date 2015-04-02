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
alignAllLines' d  
  | d == "left" = align alignLeft 
  | d == "right" = align alignRight 
  | d == "center" = align alignCenter 
  | d == "justify" = align alignJustify 
  | otherwise = error "Unknown alignment type for program (left/right/center/justify allowed)"
    where
      alignLeft num spaceConsumed words = init words ++ [(last words) ++ (take (num - spaceConsumed) (repeat ' '))]
      alignRight num spaceConsumed = reverse.(map reverse).(alignLeft num spaceConsumed).(map reverse).reverse
      alignCenter num spaceConsumed = (alignLeft num spaceConsumed).(alignRight (spaceConsumed + ((num-spaceConsumed) `div` 2)) spaceConsumed)
      alignJustify num spaceConsumed words
        | (null words || length words == 1) = alignCenter num spaceConsumed words
	| otherwise = let (w:ws) = words 
			  insertWsp = (num - spaceConsumed) `div` ((length words) - 1)
		      in  (w ++ (take insertWsp (repeat ' '))) : alignJustify (num - length w - insertWsp - 1) (spaceConsumed - length w - 1) ws

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




