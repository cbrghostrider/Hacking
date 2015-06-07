-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
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
