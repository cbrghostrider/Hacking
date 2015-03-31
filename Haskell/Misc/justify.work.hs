-- import System (getArgs)

data Justify = JLeft | JRight | JCenter deriving (Show, Eq)

--main = do
--	(filein : fileout : align : rs) <- getArgs

justifyLine :: Justify -> Int -> [Char] -> [Char]
justifyLine d n xs | d == JLeft = justifyLeft n xs'
		   | d == JRight = justifyRight n xs'
		   | otherwise = justifyCenter n xs'
	where
	  justifyLeft num cs = cs ++ take (num - length cs) (repeat ' ')
	  justifyRight num cs = reverse $ (justifyLeft num) $ reverse cs
	  justifyCenter num cs = justifyRight num $ justifyLeft (length cs + ((num - length cs) `div` 2)) $ cs
	  xs' = (deleteTrailWsp.deleteLeadWsp) xs
	  deleteLeadWsp = dropWhile (\x -> x == ' ')
	  deleteTrailWsp = reverse.deleteLeadWsp.reverse

justifyAllLines :: Justify -> Int -> [Char] -> [Char]
justifyAllLines d n = unlines.(map $ justifyLine d n).lines

