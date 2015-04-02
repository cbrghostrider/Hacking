import System.Environment (getArgs)

main :: IO ()
main = do
	args <- getArgs
	case args of 
	  [inputFile, alignType, alignVal] -> do
		input <- readFile inputFile
		writeFile (alignType++"."++inputFile) (processAlign alignType alignVal input)
	  _ -> error "Usage: ./justify inputFile alignType indentVal"

processAlign :: String -> String -> String -> String
processAlign align val input = case align of
	"left" -> alignAllLines ALeft (read val) input
	"right" -> alignAllLines ARight (read val) input
	"center" -> alignAllLines ACenter (read val) input
	"justify" -> alignAllLines AJustify (read val) input
	_ -> error "Unknown align type for program"

data Align = ALeft | ARight | ACenter | AJustify deriving (Show, Eq)

alignLine :: Align -> Int -> String -> String
alignLine d n xs | d == ALeft = alignLeft n xs'
		 | d == ARight = alignRight n xs'
		 | d == ACenter = alignCenter n xs'
		 | otherwise = alignJustify n xs'
	where
	  alignLeft num cs = cs ++ take (num - length cs) (repeat ' ')
	  alignRight num cs = reverse $ alignLeft num $ reverse cs
	  alignCenter num cs = alignRight num $ alignLeft (length cs + ((num - length cs) `div` 2)) $ cs
	  alignJustify num cs | (null cs || ((length $ words cs) == 1) || (num <= (length cs))) == True = alignCenter num cs
	  		      | otherwise = alignJustify' num cs
	  alignJustify' num cs =  let (c':cs') = words cs
	  			      insertWsp = (num - (sum $ map length $ words cs)) `div` ((length $ words cs) - 1)
				      num' = num - insertWsp - length c' 
				      c'' = alignLeft (length c' + insertWsp) c'
			          in 
				      c'' ++ alignJustify num' (unwords cs')
	  xs' = (deleteTrailWsp.deleteLeadWsp) xs
	  deleteLeadWsp = dropWhile (\x -> x == ' ')
	  deleteTrailWsp = reverse.deleteLeadWsp.reverse

alignAllLines :: Align -> Int -> String -> String
alignAllLines d n = unlines.(map $ alignLine d n).lines

