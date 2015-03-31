import System.Environment (getArgs)

-- a function that does some type of alignment on a list of words
type AlignFunc = (Int -> (Int, [String]) -> [String]) 
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
alignAllLines d n = unlines.(map unwords).(map (\ (l, ws) -> alignf n l ws)).(allLinesWithWordsPerLine n).concat.(map words).lines
  where
    alignf
      | d == "left" = alignLeft 
      | d == "right" = alignRight 
      | d == "center" = alignCenter 
      | d == "justify" = alignJustify 
      | otherwise = error "Unknown alignment type for program (left/right/center/justify allowed)"
    alignLeft num spaceConsumed words = init words ++ [(last words) ++ (take (num - spaceConsumed) (repeat ' '))]
    alignRight num spaceConsumed = reverse.(map reverse).(alignLeft num spaceConsumed).(map reverse).reverse
    alignCenter num spaceConsumed = (alignLeft num spaceConsumed).(alignRight (spaceConsumed + ((num-spaceConsumed) `div` 2)) spaceConsumed)
    alignJustify num spaceConsumed words
      | (null words || length words == 1) = alignLeft num spaceConsumed words
      | otherwise = let (w:ws) = words 
			insertWsp = (num - spaceConsumed) `div` ((length words) - 1)
 		    in  (w ++ (take insertWsp (repeat ' '))) : alignJustify (num - length w - insertWsp - 1) (spaceConsumed - length w - 1) ws

-- accumulator value is list of pairs of consumedSpace and words in line i.e [(Int, [String])]
-- foldl moves from left to right in list of all words, and creates finally --> list of lines with (consumed space, list of words in line)
allLinesWithWordsPerLine :: Int -> [String] -> [(Int, [String])]
allLinesWithWordsPerLine num = 
  foldl (\lenWdSeq word -> 
  	   let  (currLen, currWds) = last lenWdSeq
  	 	thisWs@(currLen', currWds') = if (getNewCurrLen currLen word <= num) then (getNewCurrLen currLen word, currWds ++ [word]) else (length word, [word])
		newEndSeq = if (getNewCurrLen currLen word <= num) then [thisWs] else (last lenWdSeq) : [thisWs]  
	   in   init lenWdSeq ++ newEndSeq ) 
           [(0, [])]
    where getNewCurrLen cl word = if (cl == 0) then length word else (cl + 1 + length word)



