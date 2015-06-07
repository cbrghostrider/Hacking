-- -------------------------------------------------------------------------------------
--         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
--                       For email, run on linux (perl v5.8.5):
--   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
-- -------------------------------------------------------------------------------------
import Data.List
import Data.Ord

-- take batches of pin collections, and stitches them together with an X in between
compileMemoString :: [String] -> String
compileMemoString [] = []
compileMemoString ss = foldl1' (\accstr batch -> accstr ++ "X" ++ batch) $ ss

-- groups the pins into batches of contiguous standing pins (eating Xs)
simplifyPins :: String -> [String]
simplifyPins = sortBy (comparing length) . filter  (/= []) . foldr (foldPins) [[]]
  where 
    foldPins = \pin accps -> if pin == 'X' then ([]:accps) else (pin : head accps) : tail accps

knockOneOut :: [String] -> Int -> [[String]]
knockOneOut pss seqnum = 
  let chosens = pss !! seqnum
      prior   = take seqnum pss
      later   = drop (seqnum + 1) pss
      limit   = ((length chosens) `div` 2) + ((length chosens) `mod` 2) 
      currss  = map (\n -> filter (/= []) [drop (n+1) chosens, take n chosens]) . take limit $[0..]
      retss   = map (sortBy (comparing length)) . map (\seq -> prior ++ seq ++ later) $ currss
  in  if length chosens == 1 then if null prior && null later then [] else [prior ++ later] else retss

knockTwoOut :: [String] -> Int -> [[String]]
knockTwoOut pss seqnum = 
  if length (pss !! seqnum) == 2
     then if length pss == 1 
             then []
             else [(take seqnum pss) ++ (drop (seqnum+1) pss)] 
     else knockOneOut ((take seqnum pss) ++ [tail $ (pss !! seqnum)] ++ (drop (seqnum + 1) pss)) seqnum

-- take a sequence of pins, and knocks out exactly 1 from exactly 1 batch
-- or knocks out exactly 2 contiguous from exactly 1 batch
-- and returns all such results
compilePossibilities :: [String] -> [[String]]
compilePossibilities pss = 
  let knock1Outss = concat . map (\seqnum -> knockOneOut pss seqnum) $ [0..(length pss - 1)]
      knock2Outss = concat . map (\seqnum -> knockTwoOut pss seqnum) . filter (\seqnum -> length (pss !! seqnum) >= 2) $ [0..(length pss - 1)]
  in  nub . filter (/= []) $ knock1Outss ++ knock2Outss

-- my turn to play, with the input provided. 
-- Do I win?
playGameOfKyles :: String -> Bool
playGameOfKyles []  = False  -- Last guy won, my turn lost
playGameOfKyles "I" = True   -- I can knock this out
playGameOfKyles "II" = True  -- I can knock this out
playGameOfKyles ps = 
  let sps   = simplifyPins $ ps
      posss = compilePossibilities sps
      iwin  = any (== False) . map (playGameOfKyles . compileMemoString) $ posss
  in  if null sps then False else if iwin then True else False

runTestCases :: Int -> IO ()
runTestCases 0 = return ()
runTestCases n = do
  npins <- getLine
  ps    <- getLine
  let win = playGameOfKyles (compileMemoString . simplifyPins $ ps)
  putStrLn $ if win then "WIN" else "LOSE"
  runTestCases (n-1)

main :: IO ()
main = do
  tcstr <- getLine
  runTestCases (read tcstr)

