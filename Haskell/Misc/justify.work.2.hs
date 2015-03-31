-- import System (getArgs)

--main = do
--	(filein : fileout : align : rs) <- getArgs

data Align = ALeft | ARight | ACenter | AJustify deriving (Show, Eq)

alignLine :: Align -> Int -> [Char] -> [Char]
alignLine d n xs | d == ALeft = alignLeft n xs'
		 | d == ARight = alignRight n xs'
		 | d == ACenter = alignCenter n xs'
		 | otherwise = alignJustify n xs'
	where
	  alignLeft num cs = cs ++ take (num - length cs) (repeat ' ')
	  alignRight num cs = reverse $ (alignLeft num) $ reverse cs
	  alignCenter num cs = alignRight num $ alignLeft (length cs + ((num - length cs) `div` 2)) $ cs
	  alignJustify num cs | (null cs || ((length $ words cs) == 1) || (num <= (length cs))) == True = alignCenter num cs
	  		      | otherwise = alignJustify' num cs
	  alignJustify' num cs =  let (wsAfterFirst, rest) = span (\x -> x == ' ') $ drop (length $ head $ words cs) cs
	  			      (c', cs') = ((head $ words cs) ++ wsAfterFirst, rest)
	  			      insertWsp = (num - length cs) `div` (length (words cs) - 1)
				      num' = num - insertWsp - length c' 
				      c'' = alignLeft (length c' + insertWsp) c'
			          in 
				      c'' ++ alignJustify num' cs'
	  xs' = (deleteTrailWsp.deleteLeadWsp) xs
	  deleteLeadWsp = dropWhile (\x -> x == ' ')
	  deleteTrailWsp = reverse.deleteLeadWsp.reverse

alignAllLines :: Align -> Int -> [Char] -> [Char]
alignAllLines d n = unlines.(map $ alignLine d n).lines

