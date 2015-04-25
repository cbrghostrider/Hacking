import System.Environment (getArgs)

main :: IO ()
main = do
  args <- getArgs
  case args of 
      [inputFile, alignStr, alignVal] -> do
        input <- readFile inputFile
	writeFile (alignStr++"."++alignVal++"."++inputFile) (alignAllLines (head alignStr) (read alignVal) input)
      _ -> error "Usage: ./justify inputFile alignType indentVal"

alignAllLines :: Char -> Int -> String -> String
alignAllLines d n = unlines.(map unwords).(map (\(l, ws) -> align d n l ws)).(allLinesWithWordsPerLine n).concat.(map words).lines
  where
    align 'l' num spaceConsumed words = if num == spaceConsumed then words else words ++ [take (num - spaceConsumed - 1) (repeat ' ')]
    align 'r' num spaceConsumed words = if num == spaceConsumed then words else [take (num-spaceConsumed -1) (repeat ' ')] ++ words
    align 'c' num spaceConsumed words = ((align 'l' num spaceConsumed).(align 'r' (spaceConsumed + ((num-spaceConsumed) `div` 2)) spaceConsumed)) words
    align 'j' num spaceConsumed words
      | (null words || length words == 1) = align 'l' num spaceConsumed words
      | otherwise = let (w:ws) = words 
			insertWsp = (num - spaceConsumed) `div` ((length words) - 1)
 		    in  (w ++ (take insertWsp (repeat ' '))) : align 'j' (num - length w - insertWsp - 1) (spaceConsumed - length w - 1) ws
    align _ _ _ _ = error "Unknown alignment type for program (l/r/c/j allowed)"

-- consumedSpace for a line is sum(length(words line)) + num_spaces_between_words
-- accumulator value is list of pairs of consumedSpace and list_of_words_in_line i.e [(Int, [String])]
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

