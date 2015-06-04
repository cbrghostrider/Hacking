solveProblem :: String -> String
solveProblem ss = 
  let (_, fstr, sstr) = foldr (\c acc@(tv, fls, sls) -> 
                                  if tv then (False, fls, (c:sls)) else (True, (c:fls), sls)) (True, [], []) ss
      newstr = concat $ zipWith (\c1 c2 -> c2:c1:[]) fstr sstr
  in  newstr

main :: IO ()
main = do
  ip <- getContents 
  let strs = tail . lines $ ip
  putStrLn $ unlines . map solveProblem $ strs
